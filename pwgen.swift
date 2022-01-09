//
//  main.swift
//  pwgen-cli
//
//  Created by George Watson on 17/12/2021.
//

import Foundation
import Darwin
import ArgumentParser
import AppKit

enum PWType: Int {
    case MAXIMUM = 0, LONG, MEDIUM, SHORT, BASIC, PIN, NAME, PHRASE
}

typealias fnType = @convention(c) (UnsafePointer<CChar>, UnsafePointer<CChar>, UnsafePointer<CChar>, CInt, UnsafePointer<CChar>, CInt) -> UnsafePointer<CChar>

@main
struct Args: ParsableCommand {
    @Option(name: .shortAndLong,
            help: "Set name value")
    var name: String
    @Option(name: .shortAndLong,
            help: "Set site (reference) value")
    var site: String
    @Option(name: .shortAndLong,
            help: "Set master password value")
    var pass: String = ""
    @Option(name: .shortAndLong,
            help: "Set site counter value")
    var counter: Int = 1
    @Option(name: [.customShort("k"),
                   .long],
            help: "Set key scope value, e.g. \"com.lyndir.masterpassword\"")
    var scope: String = "com.takeiteasy.password"
    @Option(name: .shortAndLong,
            help: "Set type of outputted password: (maximum, long, medium, short, basic, pin, name or phrase)",
            transform: { str in
        switch (str.lowercased()) {
        case "maximum":
            return .MAXIMUM
        case "long":
            return .LONG
        case "medium":
            return .MEDIUM
        case "short":
            return .SHORT
        case "basic":
            return .BASIC
        case "pin":
            return .PIN
        case "name":
            return .NAME
        case "phrase":
            return .PHRASE
        default:
            return .LONG
        }
    })
    var type: PWType = .LONG
    @Flag(name: [.customShort("x"),
                 .long],
          help: "Output password to clipboard")
    var clipboard: Bool = false
    
    func run() throws {
        let handle = dlopen("libpwgen.dylib", RTLD_NOW)
        defer {
            dlclose(handle)
        }
        let sym = dlsym(handle, "pw_generate")
                let fn = unsafeBitCast(sym, to: fnType.self)
        
        var password: String
        if pass.isEmpty {
            print("Please enter password for \"\(name)\"...")
            var buf = [CChar](repeating:0, count: 129)
            password = String(cString: readpassphrase("Password:", &buf, buf.count, 0))
            assert(!password.isEmpty, "Password is required")
        } else {
            password = pass
        }
        
        let ptr = fn(name, password, site, CInt(counter), scope, CInt(type.rawValue))
        let str = String(cString: ptr)
        
        if clipboard {
            let pasteboard = NSPasteboard.general
            pasteboard.declareTypes([.string], owner: nil)
            pasteboard.setString(str, forType: .string)
        } else {
            print(str)
        }
        ptr.deallocate()
    }
}
