/*  main.swift | for Minimum. */

import AppKit
import ClibTwinbeam_and_cCubist;

@available(macOS 10.15, *)
class Appdelegate: NSObject, NSApplicationDelegate {
   let controller = Windowcontroller()
   let delegate = default₋Windowdelegate()
   
   func applicationWillFinishLaunching(_ notification: Notification) {
     if let window = controller.window { window.delegate = delegate }
     print("▞ Minimum loading...please stand-by. ▚")
     let os = ProcessInfo().operatingSystemVersion
     var sha1git: UnsafePointer<CChar>?
     Gitidentity(&sha1git)
     let fingerprint = String(cString: sha1git!)
     let major=os.majorVersion, minor=os.minorVersion, patch=os.patchVersion
     print("Revision \(fingerprint) on macos version \(major).\(minor).\(patch)")
   }
   
   func applicationDidFinishLaunching(_ notification: Notification) {
     controller.showWindow(self)
     NSApp.setActivationPolicy(.regular)
     NSApp.activate(ignoringOtherApps: true)
   }
   
}

class default₋Windowdelegate: NSObject, NSWindowDelegate {
}

let app = NSApplication.shared
let delegate = Appdelegate()
app.delegate = delegate
app.run()

