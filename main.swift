/*  main.swift | for Minimum startup. */

import AppKit
import ClibTwinbeam

@available(macOS 10.15, *)
class Appdelegate: NSObject, NSApplicationDelegate {
   let controller = Windowcontroller()
   let delegate = default₋Windowdelegate()
   
   func applicationWillFinishLaunching(_ notification: Notification) {
     if let window = controller.window { window.delegate = delegate }
     print("▞ Minimum loading...please stand-by. ▚")
     let os = ProcessInfo().operatingSystemVersion
     var sha: UnsafePointer<CChar>?
     Gitidentity(&sha)
     let fingerprint = String(cString: sha!)
     let major=os.majorVersion, minor=os.minorVersion, patch=os.patchVersion
     print("Revision \(fingerprint) on macos version \(major).\(minor).\(patch)")
     /* UserDefaults.standard.register(defaults: [ UserDefaults.useDarkMode ]) */
     /* NotificationCenter.default.post(name: .appearenceChanged, object: nil) */
   }
   
   func applicationDidFinishLaunching(_ notification: Notification) {
     Include₋menu()
     controller.showWindow(self)
     NSApp.setActivationPolicy(.regular)
     NSApp.activate(ignoringOtherApps: true)
   }
   
}

extension Appdelegate {
   @objc func validateMenuItem(_ menuItem: NSMenuItem) -> Bool { print("validate menu for delegate") 
     if menuItem.action == #selector(NSApplication.orderFrontStandardAboutPanel(_:)) { return true }
     if menuItem.action == #selector(NSApplication.shared.terminate(_:)) { return true }
     return false
   }
}

func Include₋menu() { print("Building menu")
  let appmenu = NSMenuItem()
  appmenu.submenu = NSMenu()
  let about₋minimum = #selector(NSApplication.orderFrontStandardAboutPanel(_:))
  let appname = ProcessInfo.processInfo.processName
  let selector = #selector(NSApplication.shared.terminate(_:))
  appmenu.submenu?.items = [
    NSMenuItem(title: "About Minimum", action: about₋minimum, keyEquivalent: ""), 
    NSMenuItem.separator(), 
    NSMenuItem(title: "Quit \(appname)", action: selector, keyEquivalent: "q")
  ]
  let mainmenu = NSMenu(title: "Main Menu")
  mainmenu.addItem(appmenu)
  NSApplication.shared.mainMenu = mainmenu
}

class default₋Windowdelegate: NSObject, NSWindowDelegate { }

let app = NSApplication.shared
let delegate = Appdelegate()
app.delegate = delegate
app.run()

