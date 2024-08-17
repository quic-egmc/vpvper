/*
 * Copyright (c) 2019 -2022 MINRES Technologies GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Created on: Tue Feb 15 10:40:56 CET 2022
 *             *      i2c_channel.h Author: <RDL Generator>
 *
 */

#ifndef _PULPISSIMO_GEN_I2C_CHANNEL_H_
#define _PULPISSIMO_GEN_I2C_CHANNEL_H_

#include <scc/register.h>
#include <scc/tlm_target.h>
#include <scc/utilities.h>
#include <util/bit_field.h>

namespace pulpissimo {
namespace gen {

class i2c_channel_regs : public sc_core::sc_module, public scc::resetable {
public:
    //////////////////////////////////////////////////////////////////////////////
    // storage declarations
    //////////////////////////////////////////////////////////////////////////////
    uint32_t r_RX_SADDR;
    uint32_t r_RX_SIZE;
    BEGIN_BF_DECL(RX_CFG_t, uint32_t);
    BF_FIELD(CLR, 6, 1);
    BF_FIELD(PENDING, 5, 1);
    BF_FIELD(EN, 4, 1);
    BF_FIELD(DATASIZE, 1, 2);
    BF_FIELD(CONTINOUS, 0, 1);
    END_BF_DECL() r_RX_CFG;
    uint32_t r_TX_SADDR;
    uint32_t r_TX_SIZE;
    BEGIN_BF_DECL(TX_CFG_t, uint32_t);
    BF_FIELD(CLR, 6, 1);
    BF_FIELD(PENDING, 5, 1);
    BF_FIELD(EN, 4, 1);
    BF_FIELD(DATASIZE, 1, 2);
    BF_FIELD(CONTINOUS, 0, 1);
    END_BF_DECL() r_TX_CFG;
    uint32_t r_CMD_SADDR;
    uint32_t r_CMD_SIZE;
    BEGIN_BF_DECL(CMD_CFG_t, uint32_t);
    BF_FIELD(CLR, 6, 1);
    BF_FIELD(PENDING, 5, 1);
    BF_FIELD(EN, 4, 1);
    BF_FIELD(DATASIZE, 1, 2);
    BF_FIELD(CONTINOUS, 0, 1);
    END_BF_DECL() r_CMD_CFG;
    BEGIN_BF_DECL(STATUS_t, uint32_t);
    BF_FIELD(ACK, 2, 1);
    BF_FIELD(ARB_LOST, 1, 1);
    BF_FIELD(BUSY, 0, 1);
    END_BF_DECL() r_STATUS;
    BEGIN_BF_DECL(SETUP_t, uint32_t);
    BF_FIELD(DO_RST, 0, 1);
    END_BF_DECL() r_SETUP;
    //////////////////////////////////////////////////////////////////////////////
    // register declarations
    //////////////////////////////////////////////////////////////////////////////
    scc::sc_register<uint32_t> RX_SADDR;
    scc::sc_register<uint32_t> RX_SIZE;
    scc::sc_register<RX_CFG_t> RX_CFG;
    scc::sc_register<uint32_t> TX_SADDR;
    scc::sc_register<uint32_t> TX_SIZE;
    scc::sc_register<TX_CFG_t> TX_CFG;
    scc::sc_register<uint32_t> CMD_SADDR;
    scc::sc_register<uint32_t> CMD_SIZE;
    scc::sc_register<CMD_CFG_t> CMD_CFG;
    scc::sc_register<STATUS_t> STATUS;
    scc::sc_register<SETUP_t> SETUP;

    i2c_channel_regs(sc_core::sc_module_name nm);

    template <unsigned BUSWIDTH = 32> void registerResources(scc::tlm_target<BUSWIDTH>& target, uint64_t offset = 0);
};
} // namespace gen
} // namespace pulpissimo
//////////////////////////////////////////////////////////////////////////////
// member functions
//////////////////////////////////////////////////////////////////////////////

inline pulpissimo::gen::i2c_channel_regs::i2c_channel_regs(sc_core::sc_module_name nm)
: sc_core::sc_module(nm)
, NAMED(RX_SADDR, r_RX_SADDR, 0, *this)
, NAMED(RX_SIZE, r_RX_SIZE, 0, *this)
, NAMED(RX_CFG, r_RX_CFG, 0, *this)
, NAMED(TX_SADDR, r_TX_SADDR, 0, *this)
, NAMED(TX_SIZE, r_TX_SIZE, 0, *this)
, NAMED(TX_CFG, r_TX_CFG, 0, *this)
, NAMED(CMD_SADDR, r_CMD_SADDR, 0, *this)
, NAMED(CMD_SIZE, r_CMD_SIZE, 0, *this)
, NAMED(CMD_CFG, r_CMD_CFG, 0, *this)
, NAMED(STATUS, r_STATUS, 0, *this)
, NAMED(SETUP, r_SETUP, 0, *this) {}

template <unsigned BUSWIDTH>
inline void pulpissimo::gen::i2c_channel_regs::registerResources(scc::tlm_target<BUSWIDTH>& target, uint64_t offset) {
    target.addResource(RX_SADDR, 0x180UL);
    target.addResource(RX_SIZE, 0x184UL);
    target.addResource(RX_CFG, 0x188UL);
    target.addResource(TX_SADDR, 0x190UL);
    target.addResource(TX_SIZE, 0x194UL);
    target.addResource(TX_CFG, 0x198UL);
    target.addResource(CMD_SADDR, 0x1a0UL);
    target.addResource(CMD_SIZE, 0x1a4UL);
    target.addResource(CMD_CFG, 0x1a8UL);
    target.addResource(STATUS, 0x1b0UL);
    target.addResource(SETUP, 0x1b4UL);
}

#endif // _PULPISSIMO_GEN_I2C_CHANNEL_H_
