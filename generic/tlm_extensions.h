/*
 * Copyright (c) 2019 -2021 MINRES Technologies GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _SYSC_TLM_EXTENSIONS_H_
#define _SYSC_TLM_EXTENSIONS_H_

#include "tlm/scc/tlm_extensions.h"

namespace vpvper {
namespace generic {
struct tlm_signal_uart_extension : public tlm::scc::tlm_unmanaged_extension<tlm_signal_uart_extension> {

    struct uart_tx {
        unsigned data_bits : 4;
        unsigned stop_bits : 2;
        bool parity : 1;
        unsigned baud_rate : 24;
        unsigned data;
    } tx;
    sc_core::sc_time start_time;
};

struct tlm_signal_spi_extension : public tlm::scc::tlm_unmanaged_extension<tlm_signal_spi_extension> {

    struct spi_tx {
        unsigned data_bits : 5;
        bool msb_first : 1;
        bool m2s_data_valid : 1;
        bool s2m_data_valid : 1;
        unsigned m2s_data, s2m_data;
    } tx;
    sc_core::sc_time start_time;

    void copy_from(tlm_extension_base const& other) override {
        auto& o = static_cast<const type&>(other);
        this->tx = o.tx;
        this->start_time = o.start_time;
    }
};
} // namespace generic
} // namespace vpvper
#endif /* _SYSC_TLM_EXTENSIONS_H_ */
