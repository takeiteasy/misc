#!/usr/bin/env swift
//
//  adderal.swift
//  adderal
//
//  Created by George Watson on 11/12/2021.
//

import Foundation
import Dispatch
import Darwin
import IOKit.pwr_mgt

// https://vmanot.com/context-capturing-c-function-pointers-in-swift
// Not needed if running top-level code
func cFunction(_ block: (@escaping @convention(block) () -> ()))
    -> (@convention(c) () -> ()) {
    return unsafeBitCast(
        imp_implementationWithBlock(block),
        to: (@convention(c) () -> ()).self
    )
}

struct Adderal {
    static func main() {
        print("Press CTRL+C to exit: Preventing sleep...", terminator: "")
        fflush(stdout)
        
        var id:IOPMAssertionID = IOPMAssertionID(0)
        assert(IOPMAssertionCreateWithName("PreventUserIdleDisplaySleep" as CFString,
                                           IOPMAssertionLevel(kIOPMAssertionLevelOn),
                                           "com.takeiteasy.adderal" as CFString,
                                           &id) == kIOReturnSuccess,
               "ERROR: Failed to prevent sleep!")
        
        let handler: @convention(c) () -> () = cFunction {
            print("\u{8}\u{8}done!")
            IOPMAssertionRelease(id)
            exit(0)
        }
        
        var action = sigaction(__sigaction_u: unsafeBitCast(handler, to: __sigaction_u.self),
                               sa_mask: 0,
                               sa_flags: 0)
        sigaction(SIGINT, &action, nil)
        
        select(0, nil, nil, nil, nil)
    }
}
Adderal.main()
