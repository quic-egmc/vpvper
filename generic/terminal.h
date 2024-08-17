/*
 * Copyright (c) 2019 -2021 MINRES Technologies GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _SYSC_TOP_TERMINAL_H_
#define _SYSC_TOP_TERMINAL_H_

#include "cci_configuration"
#include "tlm/scc/signal_initiator_mixin.h"
#include "tlm/scc/signal_target_mixin.h"
#include "tlm/scc/tlm_signal.h"
#include <memory>
#include <sysc/kernel/sc_module.h>

namespace vpvper {
namespace generic {
class WsHandler;

class terminal : public sc_core::sc_module {
public:
    tlm::scc::tlm_signal_logic_out tx_o;
    tlm::scc::tlm_signal_logic_in rx_i;

    terminal();

    terminal(const sc_core::sc_module_name& nm);

    virtual ~terminal();

    cci::cci_param<bool> write_to_ws;

protected:
    void before_end_of_elaboration();
    void receive(tlm::scc::tlm_signal_gp<sc_dt::sc_logic>& gp, sc_core::sc_time& delay);

    std::vector<uint8_t> queue;
    std::shared_ptr<WsHandler> handler;
    sc_core::sc_time last_tx_start = sc_core::SC_ZERO_TIME;
};
} // namespace generic
} // namespace vpvper

#endif /* _SYSC_TOP_TERMINAL_H_ */
