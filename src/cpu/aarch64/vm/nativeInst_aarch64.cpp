/*
 * Copyright (c) 1997, 2010, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 *
 */

#include "precompiled.hpp"
#include "asm/macroAssembler.hpp"
#include "memory/resourceArea.hpp"
#include "nativeInst_aarch64.hpp"
#include "oops/oop.inline.hpp"
#include "runtime/handles.hpp"
#include "runtime/sharedRuntime.hpp"
#include "runtime/stubRoutines.hpp"
#include "utilities/ostream.hpp"
#ifdef COMPILER1
#include "c1/c1_Runtime1.hpp"
#endif

void NativeInstruction::wrote(int offset) {
  // FIXME: Native needs ISB here
; }


void NativeCall::verify() { ; }

address NativeCall::destination() const {
  return instruction_address() + displacement();
}

void NativeCall::print() { Unimplemented(); }

// Inserts a native call instruction at a given pc
void NativeCall::insert(address code_pos, address entry) { Unimplemented(); }

// MT-safe patching of a call instruction.
// First patches first word of instruction to two jmp's that jmps to them
// selfs (spinlock). Then patches the last byte, and then atomicly replaces
// the jmp's with the first 4 byte of the new instruction.
void NativeCall::replace_mt_safe(address instr_addr, address code_buffer) { Unimplemented(); }


void NativeMovConstReg::verify() { Unimplemented(); }


void NativeMovConstReg::print() { Unimplemented(); }

//-------------------------------------------------------------------

int NativeMovRegMem::instruction_start() const { Unimplemented(); return 0; }

address NativeMovRegMem::instruction_address() const { Unimplemented(); return 0; }

address NativeMovRegMem::next_instruction_address() const { Unimplemented(); return 0; }

int NativeMovRegMem::offset() const { Unimplemented(); return 0; }

void NativeMovRegMem::set_offset(int x) { Unimplemented(); }

void NativeMovRegMem::verify() { Unimplemented(); }


void NativeMovRegMem::print() { Unimplemented(); }

//-------------------------------------------------------------------

void NativeLoadAddress::verify() { Unimplemented(); }


void NativeLoadAddress::print() { Unimplemented(); }

//--------------------------------------------------------------------------------

void NativeJump::verify() { Unimplemented(); }


void NativeJump::insert(address code_pos, address entry) { Unimplemented(); }

void NativeJump::check_verified_entry_alignment(address entry, address verified_entry) {
  // Patching to not_entrant can happen while activations of the method are
  // in use. The patching in that instance must happen only when certain
  // alignment restrictions are true. These guarantees check those
  // conditions.
  const int linesize = 64;

  // Must be wordSize aligned
  guarantee(((uintptr_t) verified_entry & (wordSize -1)) == 0,
            "illegal address for code patching 2");
  // First 5 bytes must be within the same cache line - 4827828
  guarantee((uintptr_t) verified_entry / linesize ==
            ((uintptr_t) verified_entry + 4) / linesize,
            "illegal address for code patching 3");
}


// MT safe inserting of a jump over an unknown instruction sequence (used by nmethod::makeZombie)
// The problem: jmp <dest> is a 5-byte instruction. Atomical write can be only with 4 bytes.
// First patches the first word atomically to be a jump to itself.
// Then patches the last byte  and then atomically patches the first word (4-bytes),
// thus inserting the desired jump
// This code is mt-safe with the following conditions: entry point is 4 byte aligned,
// entry point is in same cache line as unverified entry point, and the instruction being
// patched is >= 5 byte (size of patch).
//
// In C2 the 5+ byte sized instruction is enforced by code in MachPrologNode::emit.
// In C1 the restriction is enforced by CodeEmitter::method_entry
//
void NativeJump::patch_verified_entry(address entry, address verified_entry, address dest) { Unimplemented(); }

void NativePopReg::insert(address code_pos, Register reg) { Unimplemented(); }


void NativeIllegalInstruction::insert(address code_pos) { Unimplemented(); }

void NativeGeneralJump::verify() { Unimplemented(); }


void NativeGeneralJump::insert_unconditional(address code_pos, address entry) { Unimplemented(); }


// MT-safe patching of a long jump instruction.
// First patches first word of instruction to two jmp's that jmps to them
// selfs (spinlock). Then patches the last byte, and then atomicly replaces
// the jmp's with the first 4 byte of the new instruction.
void NativeGeneralJump::replace_mt_safe(address instr_addr, address code_buffer) { Unimplemented(); }



address NativeGeneralJump::jump_destination() const { Unimplemented(); return 0; }

bool NativeInstruction::is_dtrace_trap() { Unimplemented(); return false; }
