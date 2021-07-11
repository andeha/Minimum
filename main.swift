/*  􀙤􀻒 main.swift | 'commence-initiate detail-orientation'. */

import AppKit

@available(macOS 10.15, *)
class Appdelegate: NSObject, NSApplicationDelegate {
   
   let an₋controller = Windowcontroller()
   let fork₋controller = Forkscontroller()
   lazy var appname = ProcessInfo.processInfo.processName
   let delegate = default₋Windowdelegate()
   
   func applicationWillFinishLaunching(_ notification: Notification) {
     if let window = an₋controller.window { window.delegate = delegate }
     print("▞ Minimum loading...please stand-by. ▚")
     /* NSInteger major, minor, bugfix; GetSystemVersion(major,minor,bugfix)
     print("for macos version \(major).\(minor).\(bugfix)", terminator: "") */
     /* print("a․𝘬․a \(SHA1GIT)") */
   }
   
   func applicationDidFinishLaunching(_ notification: Notification) {
     NotificationCenter.default.addObserver(self, 
      selector: #selector(thermalStateChanged(notification:)), 
      name: ProcessInfo.thermalStateDidChangeNotification, object: nil)
     include₋menu()
     an₋controller.showWindow(self)
     fork₋controller.showWindow(self)
     NSApp.setActivationPolicy(.regular)
     NSApp.activate(ignoringOtherApps: true)
   }
   
   @objc func preferences(_ sender: Any?) { print("preferences") }
   
   @objc func thermalStateChanged(notification: NSNotification) {
     let state = ProcessInfo.processInfo.thermalState
     if state == ProcessInfo.ThermalState.fair {
       debugPrint("Thermals are fair. Consider taking proactive measures to prevent higher thermals.")
     } else if state == ProcessInfo.ThermalState.serious {
       debugPrint("Thermals are highly elevated. Help the system by taking corrective action.")
     } else if state == ProcessInfo.ThermalState.critical {
       debugPrint("Thermals are seriously elevated. Help the system by taking immediate corrective action.")
     } else {
       debugPrint("Thermals are okay. Go about your business.")
     }
   }
   
   func applicationWillTerminate(_ notification: Notification) { print("to-terminate") }
   func applicationShouldTerminateAfterLastWindowClosed(_ sender: NSApplication) -> Bool { return true }
   /* func applicationShouldTerminate(_ sender: NSApplication) -> NSApplication.TerminateReply { return .terminateLater }
   func reply(toApplicationShouldTerminate shouldTerminate: Bool) { print("toApplicationShouldTerminate") } */
   
} /* ⬷ 􀈐. */

extension Appdelegate { /* ⬷ Heritage */ 
   
   func include₋menu() { print("Building menu") /* ⬷ understand /ma-n⸺v-ä-l-jer⸺f-r-å-n⸺e-n⸺me-n-y/. */
     let appmenu = NSMenuItem()
     appmenu.submenu = NSMenu()
     let about₋minimum = #selector(NSApplication.orderFrontStandardAboutPanel(_:))
     let preferences = #selector(self.preferences(_:))
     let hide₋other = #selector(NSApplication.hideOtherApplications(_:))
     appmenu.submenu?.items = [
       NSMenuItem(title: "About Minimum", action: about₋minimum, keyEquivalent: ""), 
       NSMenuItem.separator(), 
       NSMenuItem(title: "Preferences...", action: preferences, keyEquivalent: ","), 
       NSMenuItem.separator(), 
       NSMenuItem(title: "Hide \(appname)", action: #selector(NSApplication.hide(_:)), keyEquivalent: "h"), 
       NSMenuItem(title: "Hide Others", target: NSApplication.shared, action: hide₋other, 
        keyEquivalent: "h", modifier: [NSEvent.ModifierFlags.command, NSEvent.ModifierFlags.option]), 
       NSMenuItem.separator(), 
       NSMenuItem(title: "Quit \(appname)", action: #selector(NSApplication.shared.terminate(_:)), 
        keyEquivalent: "q")
     ]
     let forkmenu = NSMenuItem()
     forkmenu.submenu = NSMenu(title: "Forks")
     forkmenu.submenu?.items = [
       NSMenuItem(title: "New", action: #selector(self.preferences(_:)), keyEquivalent: "n")
     ]
    
     let editmenu = NSMenuItem()
     editmenu.submenu = NSMenu(title: "Edit")
     editmenu.submenu?.items = [
       NSMenuItem(title: "Undo", target: self, action: Selector(("undo:")), keyEquivalent: "z", 
        modifier: [NSEvent.ModifierFlags.command]), 
       NSMenuItem(title: "Redo", target: self, action: Selector(("redo:")), keyEquivalent: "z", 
        modifier: [NSEvent.ModifierFlags.command, NSEvent.ModifierFlags.shift]), 
       NSMenuItem.separator(), 
       NSMenuItem(title: "Cut", action: Selector(("cut:")), keyEquivalent: "x"), 
       NSMenuItem(title: "Copy", action: Selector(("copy:")), keyEquivalent: "c"), 
       NSMenuItem(title: "Paste", action: Selector(("paste:")), keyEquivalent: "v"), 
       NSMenuItem(title: "Select All", action: Selector(("select-all:")), keyEquivalent: "a"), 
     ]
    
     let viewmenu = NSMenuItem()
     viewmenu.submenu = NSMenu(title: "View")
     viewmenu.submenu?.items = [ /* 'add scribble' */ ]
    
     let winmenu = NSMenuItem()
     winmenu.submenu = NSMenu(title: "Window")
     winmenu.submenu?.items = [
       NSMenuItem(title: "Minimize", action: #selector(NSWindow.miniaturize(_:)), keyEquivalent: ""), 
       NSMenuItem(title: "Zoom", action: #selector(NSWindow.performZoom(_:)), keyEquivalent: ""), 
       NSMenuItem.separator(), 
       NSMenuItem(title: "Show All", action: #selector(NSApplication.arrangeInFront(_:)), keyEquivalent: "m"), 
     ]
    
     let mainmenu = NSMenu(title: "Main Menu")
     mainmenu.addItem(appmenu); mainmenu.addItem(forkmenu); mainmenu.addItem(editmenu) 
     mainmenu.addItem(viewmenu); mainmenu.addItem(winmenu)
     /* mainmenu.addItems(appmenu, forkmenu, editmenu, viewmenu, winmenu) */
     NSApplication.shared.mainMenu = mainmenu /* ⬷ NSResponder object. */
   }
  
   @objc func validateMenuItem(_ menuItem: NSMenuItem) -> Bool { print("validate menu for delegate") 
     if menuItem.action == #selector(NSApplication.orderFrontStandardAboutPanel(_:)) { return true }
     if menuItem.action == #selector(self.preferences(_:)) { return true }
     if menuItem.action == #selector(NSApplication.hide(_:)) { return true }
     if menuItem.action == #selector(NSApplication.hideOtherApplications(_:)) { return true }
     if menuItem.action == #selector(NSApplication.shared.terminate(_:)) { return true }
     return false
   }
  
}

extension Notification.Name {
  static let searchitem₋found = Notification.Name("􀊬-found")
  static let preferences₋changed = Notification.Name("􀣔-preferences") /* todo: improve 􀯛. */
} /* ⬷ c𝘧․ a Scandinavian 'grottmålning'. */

let app = NSApplication.shared
let delegate = Appdelegate()
app.delegate = delegate
app.run()


