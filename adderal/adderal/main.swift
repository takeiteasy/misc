#!/usr/bin/env swift
//
//  main.swift
//  adderal
//
//  Created by George Watson on 11/12/2021.
//

import Foundation
import Dispatch
import Darwin
import IOKit.pwr_mgt

print("Press CTRL+C to exit: Preventing sleep...", terminator: "")
fflush(stdout)

var id:IOPMAssertionID = IOPMAssertionID(0)
assert(IOPMAssertionCreateWithName("PreventUserIdleDisplaySleep" as CFString,
                                   IOPMAssertionLevel(kIOPMAssertionLevelOn),
                                   "com.takeiteasy.unwake" as CFString,
                                   &id) == kIOReturnSuccess,
       "ERROR: Failed to prevent sleep!")

let handler: @convention(c) (Int32) -> () = { sig in
    print("\u{8}\u{8}done!")
    IOPMAssertionRelease(id)
    exit(0)
}

var action = sigaction(__sigaction_u: unsafeBitCast(handler, to: __sigaction_u.self),
                       sa_mask: 0,
                       sa_flags: 0)
sigaction(SIGINT, &action, nil)

select(0, nil, nil, nil, nil)
