/* 􀙤􀻒 main.swift | 'commence-initiate detail-orientation'. */

import AppKit
import Metal

class Minimumview: NSView {
  
  override init(frame frameRect: NSRect) { print("minimumview-init") 
    super.init(frame: frameRect)
    self.wantsLayer = true
    DispatchQueue.main.asyncAfter(deadline: .now() + .seconds(1)) {
      let update = NSRect(x: 0, y: 0, width: 10, height: 10)
      print("setNeedsDisplay \(update)")
      self.setNeedsDisplay(update)
    }
  }
  
  required init?(coder: NSCoder) {
    fatalError("init(coder:) not implemented")
  }
  
  let paper = NSColor(calibratedWhite: 0.95, alpha: 1.0), 
   paperborder = NSColor(calibratedWhite: 0.75, alpha: 1.0)
  let cropmarks = NSColor(calibratedWhite: 0.70, alpha: 1.0)
  let fine₋grid = NSColor(calibratedWhite: 0.92, alpha: 1.0), 
   coarse₋grid = NSColor(calibratedWhite: 0.88, alpha: 1.0)
  let systemfont = NSFont.systemFont(ofSize: 30.0)
  let textcolor = NSColor(named: NSColor.Name("primaryControlColor"))
  let frame₋anfang = NSRect(x: 120.0, y: 50.0, width: 48.0, height: 48.0)
  
  var non₋kernel₋images = Array<CGImage>()
  
  var y₋offset : CGFloat = 0.0 /* ⬷ visible rect, overdraw and underdraw. */
  var x₋offset : CGFloat = 0.0 /* ⬷ allows for horizontal scrolling including max line length in document. */ 
  
  let Operations₁ = DispatchQueue(label: "myops", attributes: .concurrent) /* ⬷ for visible work. */
  let Operations₂ = DispatchQueue(label: "myjobs" /* , attributes: .serial */) /* ⬷ for non-visible work. */
  /* ⬷ samgörande alt․ schemalaggda (▚). */
  
  var mouseIsOver: Bool = false /* ⬷ you should hit₋test this on init. */
  var hasMouseEntered: Bool = false /* ⬷ you should hit₋test this on init. */
  
  let textlayer = CATextLayer()
  var layers₋with₋images = Array<CALayer>()
  var layers₋with₋simulations = Array<CAMetalLayer>()
  var layers₋with₋vectors = Array<CAShapeLayer>()
  let layerdelegate = Layerdelegate()
  let composition = CALayer()
  /* ⬷ 𝘤𝘧․ against var layer: NSView.CALayer. */
  
  enum type₋of₋layer { case image; case simulation; case vector }
  
  func add(type: type₋of₋layer, initial: NSPoint, size: NSSize) {
    switch type {
    case .image:
     typealias ImageLayer = CALayer
     let layer = ImageLayer()
     layers₋with₋images.append(layer)
    case .simulation:
     let layer = CAMetalLayer()
     layers₋with₋simulations.append(layer)
    case .vector:
     let layer = CAShapeLayer()
     layers₋with₋vectors.append(layer) 
    }
  }
  
  override var isOpaque: Bool { false }
  override var isFlipped: Bool { true }
  override var wantsUpdateLayer: Bool { true }
  /* override var wantsDefaultClipping: Bool { false } */
  /* override var canDrawSubviewsIntoLayer: Bool { true } */
  /* override var layerUsesCoreImageFilters */
  /* backgroundFilters, composingFilters and contentFilters. */
  override func makeBackingLayer() -> CALayer {
    composition.delegate = self.layerdelegate
    composition.needsDisplayOnBoundsChange = true
    return composition }
  override func viewWillMove(toWindow: NSWindow?) {
    print("viewWillMoveToWindow") 
    super.viewWillMove(toWindow: window) }
  override func viewWillMove(toSuperview: NSView?) {
    print("viewWillMoveToSuperview")
    super.viewWillMove(toSuperview: toSuperview) }
  override func updateLayer() { print("updateLayer") 
    super.updateLayer() 
    guard let ctx = NSGraphicsContext.current?.cgContext else { return }
    let path = NSBezierPath()
    path.move(to: NSPoint(x: 0, y: 0))
    path.line(to: NSPoint(x: 10, y: 10))
    path.stroke() }
  func render₋image() -> CGImage? {
    let omgivning = CGContext(data: nil, width: 20, height: 20, 
     bitsPerComponent: 8, bytesPerRow: 0, 
     space: CGColorSpace(name: CGColorSpace.sRGB)!, 
     bitmapInfo: CGImageAlphaInfo.premultipliedLast.rawValue)!
    let ns₋omgivning = NSGraphicsContext(cgContext: omgivning, flipped: true)
    NSGraphicsContext.current = ns₋omgivning; do {
      let path = NSBezierPath()
      path.move(to: .init(x: 10.5, y: 10.5))
      path.line(to: .init(x: 10.5, y: 10.5))
      path.lineWidth = 1
      path.lineCapStyle = .round
      NSColor.blue.set()
      path.stroke()
    }
    NSGraphicsContext.current = nil
    return omgivning.makeImage()
  }
  
  override func draw(_ dirty: CGRect) { print("draw-rect: \(dirty)") 
    
    guard let omgivning = NSGraphicsContext.current?.cgContext else { return }
    
    print("self.frame now is \(self.frame)")
    
    /* a small drawing-machine... */
    
    super.draw(dirty)
  }
  
}

class Viewcontroller: NSViewController {
  
  init() { print("viewcontroller-init"); super.init(nibName: nil, bundle: nil) }
  
  required init?(coder: NSCoder) { fatalError("init(coder:) has not been implemented") }
  
  override func loadView() { print("Loading view") 
    let initial₋placement = NSPoint(x: 0, y: 0) /* ⬷ unused. */
    let initial₋rect = NSSize(width: 501, height: 502) /* ⬷ construe and merged later. */
    let frame = NSRect(origin: initial₋placement, size: initial₋rect)
    let visualeffect = NSVisualEffectView(frame: frame)
    visualeffect.translatesAutoresizingMaskIntoConstraints = false
    visualeffect.blendingMode = .behindWindow
    visualeffect.state = .active
    /* visualeffect.layer?.cornerRadius = 16.0 */
    self.view = visualeffect
    let material = Minimumview(frame: frame)
    self.view.addSubview(material)
    NSLayoutConstraint.activate([
     material.leadingAnchor.constraint(greaterThanOrEqualTo: visualeffect.safeAreaLayoutGuide.leadingAnchor, constant: 20), 
     material.trailingAnchor.constraint(greaterThanOrEqualTo: visualeffect.safeAreaLayoutGuide.trailingAnchor, constant: 20), 
     material.topAnchor.constraint(greaterThanOrEqualTo: visualeffect.safeAreaLayoutGuide.topAnchor, constant: 20), 
     material.bottomAnchor.constraint(greaterThanOrEqualTo: visualeffect.safeAreaLayoutGuide.bottomAnchor, constant: 20)
    ])
    self.view.allowedTouchTypes = [.direct, .indirect]
  }
  
  override func viewDidLoad() { print("viewDidLoad") 
    /* bind(NSBindingName(rawValue: #keyPath(touchBar)), to: self, 
     withKeyPath: #keyPath(touchBar), options: nil) */
  }
  
  override func viewDidAppear() { print("viewDidAppear") 
    print("viewDidAppear 'frame' now is \(self.view.frame)")
    print("viewDidAppear view now is \(self.view)") 
  }
  
  override func viewDidDisappear() { super.viewDidDisappear(); print("viewDidDisappear") }
  
  override var acceptsFirstResponder: Bool { true }
  
  override func mouseEntered(with event: NSEvent) { print("mouseentered") }
  /* 􀑆 */
  /* 𐤟𐤟𐤟 */
  /* 􀞷 */
  
  func addScribblelayer(sender: AnyObject)
  {
     print("Adding Scribbleview")
  }
  
}

class Windowcontroller: NSWindowController {
   
   let viewctrl = Viewcontroller()
   var shell = Inter₋act₋and₋inte₋r₋u₋p₋t()
   
   convenience init() { print("windowcontroller-convenience-init") 
     self.init(window: nil)
   }
   
   override init(window: NSWindow?) { print("windowcontroller-window-init") 
     super.init(window: window)
   }
   
   required init?(coder: NSCoder) {
     fatalError("init(coder:) has not been implemented")
   }
   
   override func showWindow(_ sender: Any?) { print("showWindow") 
     windowWillLoad() /* ⬷ one non-indicative correct. */
     loadWindow()
     windowDidLoad() /* ⬷ a second non-indicative correct. */
     window?.makeKeyAndOrderFront(sender)
   }
   
   override func loadWindow() { print("loadWindow") 
     let window = Minimumwindow(contentViewController: self.viewctrl)
     print("window.frame is \(window.frame)")
     print("viewctrl.view.frame is \(viewctrl.view.frame)")
     self.window = window
   }
   
   override func windowDidLoad() { print("windowDidLoad"); reloadUi() 
     NotificationCenter.receive(.preferencesChanged, 
      instance: self, selector: #selector(reloadUi))
     let out = { (material: Data) in 
      let text = String(bytes: material, encoding: String.Encoding.utf8)
      print("message: \(String(describing: text))") }
     /* let y = shell.occurrent₋spawn(execute: "ls", parameters: ["-l", "-a"], out: out)
     if y != 0 { print("unable to spawn") } */
   }
   
   @objc private func reloadUi() { print("reloadUi") 
     
     if #available(OSX 10.14, *) {
       if NSApp.effectiveAppearance.name == .darkAqua { return }
     }
     
     
     // if theme.background.isDark {
       window?.appearance = NSAppearance(named: .darkAqua)
     // } else {
       window?.appearance = NSAppearance(named: .aqua)
     // }
   }
   
} /* ⬷ 𝘊𝘧․ Windowcontroller and Ieee754-Opt. */

class Minimumwindow: NSWindow {
  
   convenience init(contentViewController: NSViewController) {
     print("Minimumwindow-convenience-init \(contentViewController)")
     let initial₋placement = NSPoint(x: 928, y: 10)
     let initial₋rect = NSSize(width: 0, height: 0) /* ⬷ unused a․𝘬․a /zip/. */
     let mask: StyleMask = [ .borderless, .closable, .miniaturizable, .resizable, 
       /* .fullScreen, */ .fullSizeContentView ]
     self.init(contentRect: NSRect(origin: initial₋placement, size: initial₋rect), 
       styleMask: mask, backing: .buffered, defer: false)
 //    isMovableByWindowBackground = true
     /* collectionBehavior = [.canJoinAllSpaces]
     collectionBehavior = [.moveToActiveSpace, .ignoresCycle] */
     self.contentViewController = contentViewController
   }
   
   override var canBecomeKey: Bool { get { return true } }
   
   override func keyDown(with event: NSEvent) {
     let minimumview = self.contentViewController!.view.subviews[0] as! Minimumview
     minimumview.Operations₂.async {
      /* DispatchQueue.main.async { } */
      print("keydown \(event.keyCode)")
      print("keydown \(String(describing: event.characters))")
     }
   }
   
   override func performKeyEquivalent(with: NSEvent) -> Bool { print("performKeyEquivalent"); return false; }
   
   override func flagsChanged(with event: NSEvent) {
     print("shiftR-optR-cmdR-cmdL-optL-ctrl-fn-shiftL")
     print("keydown \(event.keyCode)")
   }
   
/* NSInsertFunctionKey, NSDeleteFunctionKey, NSClearLineFunctionKey, 
  NSClearDisplayFunctionKey, NSFindFunctionKey, NSModeSwitchFunctionKey. NSPageUpFunctionKey, 
  NSPageDownFunctionKey, NSPrintScreenFunctionKey, NSPauseFunctionKey, NSBreakFunctionKey, 
  NSStopFunctionKey, NSResetFunctionKey, NSPrintFunctionKey, NSInsertCharFunctionKey, 
  NSUndoFunctionKey, NSRedoFunctionKey. */
   
}

@available(macOS 10.15, *)
class Appdelegate: NSObject, NSApplicationDelegate {
   
   let controller = Windowcontroller()
   let fork₋controller = Forkscontroller()
   let delegate = Delegate()
   
   func applicationWillFinishLaunching(_ notification: Notification) {
     if let window = controller.window { window.delegate = delegate }
     print("▞ Minimum loading...please stand-by. ▚")
     /* NSInteger major, minor, bugfix; GetSystemVersion(major,minor,bugfix)
     print("for macos version \(major).\(minor).\(bugfix)", terminator: "") */
     /* print("a․𝘬․a \(SHA1GIT)") */
   }
   
   func applicationDidFinishLaunching(_ notification: Notification) {
     if let window = controller.window {
       window.setFrameAutosaveName("Minimum-Window")
       /* window.center() */
       
       let appMenu = NSMenuItem()
       appMenu.submenu = NSMenu()
       appMenu.submenu?.addItem(NSMenuItem(title: "Quit", action: #selector(NSApplication.terminate(_:)), keyEquivalent: "q"))
       let mainMenu = NSMenu(title: "Minimum")
       mainMenu.addItem(appMenu)
       NSApplication.shared.mainMenu = mainMenu
       
       NotificationCenter.default.addObserver(self, 
        selector: #selector(thermalStateChanged(notification:)), 
        name: ProcessInfo.thermalStateDidChangeNotification, object: nil)
       
      /* for await note in NotificationCenter.default.notifications(
        named: ProcessInfo.thermalStateDidChangeNotification) {
         // use note.
       } */
     }
     controller.showWindow(self)
     fork₋controller.showWindow(self)
     NSApp.setActivationPolicy(.regular)
     NSApp.activate(ignoringOtherApps: true)
   }
   
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
   func applicationShouldTerminate(_ sender: NSApplication) -> NSApplication.TerminateReply { return .terminateLater }
   func reply(toApplicationShouldTerminate shouldTerminate: Bool) { print("toApplicationShouldTerminate") }
   
   /* @objc override func validateMenuItem(_ menuItem: NSMenuItem) -> Bool { return true } */
   /* if menuItem.action == #selector(NSApplication.toggleTouchBarCustomizationPalette(_:)) { return true } */
   
}

let app = NSApplication.shared
let delegate = Appdelegate()
app.delegate = delegate
app.run()


