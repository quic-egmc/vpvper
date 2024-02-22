/*
 * Copyright (c) 2019 -2021 MINRES Technologies GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _QSPI_H_
#define _QSPI_H_

#include <scc/tlm_target.h>
#include <scc/clock_if_mixins.h>
#include <sysc/communication/sc_signal_ports.h>
#include <scc/memory.h>

namespace vpvper {
namespace minres {

class Apb3SpiXdrMasterCtrl_regs;

class qspi : public sc_core::sc_module, public scc::tlm_target<> {
public:
    SC_HAS_PROCESS(qspi);// NOLINT

    sc_core::sc_in<bool> rst_i{"rst_i"};

    sc_core::sc_out<bool> ssclk_o{"ssclk_o"};

    sc_core::sc_vector<sc_core::sc_out<bool>> dq_o{"dq_o", 4};

    sc_core::sc_vector<sc_core::sc_out<bool>> oe_o{"oe_o", 4};

    sc_core::sc_vector<sc_core::sc_in<bool>> dq_i{"dq_i", 4};

    sc_core::sc_out<bool> irq_o{"irq_o"};

    tlm::tlm_target_socket<scc::LT> xip_sck{"xip_sck"};

    qspi(sc_core::sc_module_name nm);

    virtual ~qspi() override; // need to keep it in source file because of fwd declaration of spi_regs

    void set_clock_period(sc_core::sc_time period) {
        clk_period=period;
    }

protected:
    void reset_cb();
    sc_core::sc_time clk_period;
    std::unique_ptr<Apb3SpiXdrMasterCtrl_regs> regs;
    scc::memory<16_MB, scc::LT> flash_mem {"flash_mem"};

};

using qspi_tl = scc::tickless_clock<qspi>;
using qspi_tc = scc::ticking_clock<qspi>;

} /* namespace minres */
} /* namespace vpvper */

#endif /* _QSPI_H_ */
