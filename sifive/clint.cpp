/*
 * Copyright (c) 2019 -2021 MINRES Technologies GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "clint.h"
#include "gen/clint_regs.h"

#include "scc/report.h"
#include "scc/utilities.h"

namespace vpvper {
namespace sifive {
using namespace sc_core;

const int lfclk_mutiplier = 1 << 12;

clint::clint(sc_core::sc_module_name nm)
: sc_core::sc_module(nm)
, tlm_target<>(clk)
, NAMED(tlclk_i)
, NAMED(lfclk_i)
, NAMED(rst_i)
, NAMED(mtime_int_o)
, NAMED(msip_int_o)
, NAMEDD(regs, clint_regs)
, cnt_fraction(0) {
    regs->registerResources(*this);
    SC_METHOD(clock_cb);
    sensitive << tlclk_i << lfclk_i;
    SC_METHOD(reset_cb);
    sensitive << rst_i;
    dont_initialize();
    regs->mtimecmp.set_write_cb([this](scc::sc_register<uint64_t>& reg, uint64_t data, sc_core::sc_time d) -> bool {
        if(!regs->in_reset()) {
            reg.put(data);
            this->update_mtime();
        }
        return true;
    });
    regs->mtime.set_read_cb([this](const scc::sc_register<uint64_t>& reg, uint64_t& data, sc_core::sc_time d) -> bool {
        this->update_mtime();
        data = reg.get();
        return true;
    });
    regs->mtime.set_write_cb([this](scc::sc_register<uint64_t>& reg, uint64_t data, sc_core::sc_time d) -> bool {
        if(!regs->in_reset()) {
            reg.put(data);
            this->update_mtime();
        }
        return true;
    });
    regs->msip.set_write_cb([this](scc::sc_register<uint32_t>& reg, uint32_t data, sc_core::sc_time d) -> bool {
        reg.put(data);
        msip_int_o.write(regs->r_msip.msip);
        return true;
    });
    SC_METHOD(update_mtime);
    sensitive << mtime_evt;
    dont_initialize();
}

void clint::clock_cb() {
    update_mtime();
    clk = lfclk_i.read();
    update_mtime();
}

clint::~clint() = default;

void clint::reset_cb() {
    if(rst_i.read()) {
        regs->reset_start();
        msip_int_o.write(false);
        mtime_int_o.write(false);
        cnt_fraction = 0;
    } else
        regs->reset_stop();
}

void clint::update_mtime() {
    if(clk > SC_ZERO_TIME) {
        uint64_t elapsed_clks =
            (sc_time_stamp() - last_updt) / clk; // get the number of clock periods since last invocation
        last_updt += elapsed_clks * clk;         // increment the last_updt timestamp by the number of clocks
        if(elapsed_clks) {                       // update mtime reg if we have more than 0 elapsed clk periods
            regs->r_mtime += elapsed_clks;
            mtime_evt.cancel();
            if(regs->r_mtimecmp > 0) {
                if(regs->r_mtimecmp > regs->r_mtime && clk > sc_core::SC_ZERO_TIME) {
                    sc_core::sc_time next_trigger =
                        (clk * lfclk_mutiplier) * (regs->r_mtimecmp - regs->mtime) - cnt_fraction * clk;
                    SCCTRACE() << "Timer fires at " << sc_time_stamp() + next_trigger;
                    mtime_evt.notify(next_trigger);
                    mtime_int_o.write(false);
                } else {
                    mtime_int_o.write(true);
                }
            }
        }
    } else
        last_updt = sc_time_stamp();
}

} /* namespace sifive */
} /* namespace vpvper */
