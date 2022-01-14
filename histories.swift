/*  histories.swift | the Minimum log. */

import AppKit
import ClibTwinbeam_and_cCubist;
import Metal /* ⬷ alt․ AppKit + Metal. */

class Rendition {
   
   static let zinkwhite = NSColor(calibratedWhite: 0.99, alpha: 1.0)
   static let systemfont = NSFont.systemFont(ofSize: 30.0), 
    textfont = NSFont(name: "SF Mono", size: 11)!
   
   var default₋textattrs: [NSAttributedString.Key: Any] {
     get {
       let ink = Rendition.zinkwhite.cgColor
       return [.font: Rendition.textfont, .foregroundColor: ink]
     }
   }
   
   var utf8₋bytes = Array<UInt8>()
   var unicodes = Array<UInt32>()
   var linebreaks = Array<Int>() /* ⬷ a․𝘬․a lf₋locations. */
   var y₋offset = 0.0
   
   func line₋height(font: NSFont) -> CGFloat {
     let fontLineHeight = CTFontGetAscent(font) + CTFontGetDescent(font) + CTFontGetLeading(font)
     return fontLineHeight
   }
   
   func text₋height(font: NSFont) -> CGFloat
   {
     return CGFloat(linebreaks.count + 1)*line₋height(font: font)
   }
   
   func edit₋height(font: NSFont) -> CGFloat
   {
     return line₋height(font: font)
   }
   
   func document₋height(font: NSFont) -> CGFloat
   {
     return text₋height(font: font) + edit₋height(font: font)
   }
   
}

class Minimumwindow: NSWindow {
   
   convenience init(contentViewController: NSViewController) {
     print("Minimumwindow-convenience-init \(contentViewController)")
     let initial₋placement = NSPoint(x: 928, y: 10)
     let initial₋rect = NSSize(width: 0, height: 0) /* ⬷ unused a․𝘬․a /zip/ alt․ 􀆔+􀆝+4 from NSViewController. */
     let mask: StyleMask = [ .borderless, .closable, .miniaturizable, .resizable, 
       /* .fullScreen, */ .fullSizeContentView ]
     self.init(contentRect: NSRect(origin: initial₋placement, size: initial₋rect), 
       styleMask: mask, backing: .buffered, defer: false)
     self.setFrameAutosaveName("Minimum-Window")
     isMovableByWindowBackground = true
     self.contentViewController = contentViewController
   } /* ⬷ superflous 'if let window = an₋controller.window { window.center() }'. */
   
   override var canBecomeKey: Bool { true }
   
   var shift=false, ctrl=false, opt=false, cmd=false
   
   override func flagsChanged(with event: NSEvent) {
     let modifs: NSEvent.ModifierFlags = event.modifierFlags
     shift = modifs.contains(.shift)
     ctrl = modifs.contains(.control)
     opt = modifs.contains(.option)
     cmd = modifs.contains(.command)
     print("flagsChanged: \(shift), \(ctrl), \(opt), \(cmd)")
   }
   
   override func performKeyEquivalent(with event: NSEvent) -> Bool {
     print("performKeyEquivalent")
     return super.performKeyEquivalent(with: event)
   }
   
   override func noResponder(for event: Selector) { print("no responder for \(event)") }
   
}

class Minimumview: NSView {
   override init(frame frameRect: NSRect) {
     print("minimumview-init")
     super.init(frame: frameRect)
     self.layerContentsRedrawPolicy = NSView.LayerContentsRedrawPolicy.onSetNeedsDisplay
     let later₋future: DispatchTime = .now() + .seconds(1)
     DispatchQueue.main.asyncAfter(deadline: later₋future) {
       let frame₋update = NSRect(x: 0, y: 0, width: self.frame.width, 
        height: self.frame.height)
       print("setNeedsDisplay \(frame₋update)")
       self.needsDisplay = true
     }
     /* init₋for₋dropping(NSFilenamesPboardType) */
    /* self.rotate(byDegrees: 10.0)
    self.translateOrigin(to: NSPoint(x: 100.0, y: 100.0))
    self.scaleUnitSquare(to: NSSize(width: 1.0, height: 1.0)) */
   }
   
   required init?(coder: NSCoder) {
     fatalError("init(coder:) not implemented")
   }
   
   override var isOpaque: Bool { false }
   
   var controller: Viewcontroller {
     get { self.window!.contentViewController as! Viewcontroller }
     set { self.window!.contentViewController = newValue }
   }
   
   override func setFrameSize(_ newSize: NSSize) {
     print("setFrameSize to \(newSize)")
     super.setFrameSize(newSize)
   }
   
   func setNeedsDisplay(_ uc₋count: Int, _ break₋count: Int) {
     print("setNeedsDisplay \(uc₋count), \(break₋count)")
     print("setNeedsDisplay \(self.frame)")
     //self.setNeedsDisplay(self.bounds)
   }
   
}

extension Minimumview { /* ⬷ text drawing. */
   
   override func draw(_ dirty: CGRect) {
     print("draw-rect: \(dirty) self.frame now is \(self.frame)")
     guard let context = NSGraphicsContext.current?.cgContext else { return }
     self.controller.rendition.unicodes.withUnsafeBytes {
       let raw = UnsafeMutableRawPointer(mutating: $0.baseAddress!)
       let count = self.controller.rendition.unicodes.count
       let text = String(bytesNoCopy: raw, length: 4*count, encoding: 
         .utf32LittleEndian, freeWhenDone: false)
       let default₋textattrs = self.controller.rendition.default₋textattrs
       let attributed = NSAttributedString(string: text!, attributes: default₋textattrs)
       let y₋offset = self.controller.rendition.y₋offset
       var rect = self.frame.offsetBy(dx: 0, dy: y₋offset)
       rect.origin.y = rect.origin.y - 1000 + rect.size.height
       rect.size.height = 1000
       Typeset(attributed, frame: rect, context: context)
     }
     /* let first₋unicode=0, last₋unicode=0
     self.viewcontroller.rendition.forEach.linebreaks { elem in } */
     super.draw(dirty)
   }
}

class Viewcontroller: NSViewController {
   
   init() { print("viewcontroller-init"); super.init(nibName: nil, bundle: nil) }
   
   required init?(coder: NSCoder) { fatalError("init(coder:) has not been implemented") }
   
   override func loadView() { print("Loading View") 
     let initial₋placement = NSPoint(x: 0, y: 0) /* ⬷ unused. */
     let initial₋rect = NSSize(width: 501, height: 502) /* ⬷ construe and merged later. */
     let frame = NSRect(origin: initial₋placement, size: initial₋rect)
     let visualeffect = NSVisualEffectView(frame: frame)
     /* visualeffect.translatesAutoresizingMaskIntoConstraints = false */
     visualeffect.blendingMode = .behindWindow
     visualeffect.state = .active
     self.view = visualeffect
     let material = Minimumview(frame: frame)
     /* material.acceptsTouchEvents = true */
     material.allowedTouchTypes = [.indirect] /* ⬷ ipad = .direct */
     self.view.addSubview(material)
     let views = [ "material" : minimumview ]
     self.view.addConstraints(NSLayoutConstraint.constraints(withVisualFormat: "|[material]|", options: [], metrics: nil, views: views))
     self.view.addConstraints(NSLayoutConstraint.constraints(withVisualFormat: "V:|[material]|", options: [], metrics: nil, views: views))
     material.translatesAutoresizingMaskIntoConstraints = false
   }
   
   override func viewDidLoad() { print("viewDidLoad") 
     /* bind(NSBindingName(rawValue: #keyPath(touchBar)), to: self, 
      withKeyPath: #keyPath(touchBar), options: nil) */
   }
   
   override func viewDidAppear() { print("viewDidAppear") 
     print("viewDidAppear view now is \(self.view)")
     print("viewDidAppear 'frame' now is \(self.view.frame)")
   }
   
   override func viewDidDisappear() { super.viewDidDisappear(); print("viewDidDisappear") }
   
   var rendition: Rendition {
     get { self.representedObject as! Rendition }
     set { self.representedObject = newValue 
      minimumview.needsDisplay = true }
   }
   
   var minimumview: Minimumview { get { self.view.subviews[0] as! Minimumview } }
   
   override var acceptsFirstResponder: Bool { true }
   
   func vertical₋scroll(_ plus₋minus₋1: CGFloat)
   {
     let document₋height = rendition.document₋height(font: Rendition.textfont)
     let view₋height = self.view.subviews[0].bounds.height
     if (document₋height <= view₋height) { return }
     rendition.y₋offset += view₋height*plus₋minus₋1
     if (rendition.y₋offset < 0) { rendition.y₋offset = 0 }
     if (document₋height - rendition.y₋offset < view₋height) {
       rendition.y₋offset = document₋height - view₋height }
     print("\(document₋height) and \(view₋height) and \(rendition.y₋offset)")
     minimumview.needsDisplay = true
   }
   
   var beginning₋touches = Dictionary<String,NSPoint>()
   var moved₋touches = Dictionary<String,NSPoint>()
   
   func key(_ oval: NSTouch) -> String { return "\(oval.identity)" }
   
   override func touchesBegan(with event: NSEvent) {
     /* let instant: TimeInterval = event.timestamp */
     let ovals = event.touches(matching: .began, in: view)
     for oval in ovals {
       let identity = key(oval)
       beginning₋touches[identity] = oval.normalizedPosition
     }
   }
   
   override func touchesMoved(with event: NSEvent) {
     /* let instant: TimeInterval = event.timestamp */
     let ovals = event.touches(matching: .moved, in: view)
     for oval in ovals {
       let identity = key(oval)
       moved₋touches[identity] = oval.normalizedPosition
     }
     if ovals.count == 2 {
       let 𝟶: Set<NSTouch>.Index = ovals.index(ovals.startIndex, offsetBy: 0)
       let 𝟷: Set<NSTouch>.Index = ovals.index(ovals.startIndex, offsetBy: 1)
       let first=key(ovals[𝟶]), second=key(ovals[𝟷])
       let distance₁ = moved₋touches[first]!.y - beginning₋touches[first]!.y
       let distance₂ = moved₋touches[second]!.y - beginning₋touches[second]!.y
       let magnitude = (distance₁ + distance₂) / 2
       print("two-finger swipe \(magnitude)")
       vertical₋scroll(magnitude)
       /* top to botton prints magnitude from 0 to approximately -0.97. */
       let rect: CGRect = minimumview.frame
       let physical₋size = ovals[𝟶].deviceSize
       minimumview.needsDisplay = true
     }
   }
  
   override func touchesEnded(with event: NSEvent) {
     /* let instant: TimeInterval = event.timestamp */
     let ovals = event.touches(matching: .ended, in: view)
     for oval in ovals {
       let identity = key(oval)
       beginning₋touches.removeValue(forKey: identity)
       moved₋touches.removeValue(forKey: identity)
     }
   }
  
   override func pressureChange(with event: NSEvent) {
     /* let instant: TimeInterval = event.timestamp */
     let pressure = event.pressure
     print("pressure \(pressure)")
   }
   
   override func touchesCancelled(with event: NSEvent) { print("touchesCancelled") }
   
}

class Windowcontroller: NSWindowController {
   
   convenience init() {
     print("windowcontroller-convenience-init")
     self.init(window: nil)
   }
   
   override init(window: NSWindow?) {
     print("windowcontroller-window-init")
     super.init(window: window)
   }
   
   required init?(coder: NSCoder) {
     fatalError("init(coder:) has not been implemented")
   }
   
   override func showWindow(_ sender: Any?) {
     print("showWindow")
     windowWillLoad()
     loadWindow()
     windowDidLoad()
     window?.makeKeyAndOrderFront(sender)
   }
   
   override func loadWindow() {
     print("loadWindow")
     let window = Minimumwindow(contentViewController: self.viewctrl)
     print("window.frame is \(window.frame)")
     print("viewctrl.view.frame is \(viewctrl.view.frame)")
     self.window = window
   }
   
   let viewctrl = Viewcontroller()
   var shell = Interaction()
   
   var minimumwindow: Minimumwindow { self.window as! Minimumwindow }
   var minimumview: Minimumview { viewctrl.view.subviews[0] as! Minimumview }
   var rendition: Rendition { viewctrl.representedObject as! Rendition }
   
   var utf8₋bytes₋idx: Int = 0;
   let maxfour = UnsafeMutablePointer<UInt8>.allocate(capacity: 4)
   
   override func windowDidLoad() { print("windowDidLoad") 
     self.viewctrl.representedObject = Rendition()
     shell.output = { (material: Data) in 
       material.forEach { elem in self.rendition.utf8₋bytes.append(elem) }
       let uc₋count = self.rendition.unicodes.count
       let break₋count = self.rendition.linebreaks.count
       while self.utf8₋bytes₋idx < self.rendition.utf8₋bytes.count {
         let leadOr8Bit = self.rendition.utf8₋bytes[self.utf8₋bytes₋idx]
         let followers = Int(Utf8Followers(leadOr8Bit))
         if self.utf8₋bytes₋idx + followers < self.rendition.utf8₋bytes.count {
           self.maxfour[0] = leadOr8Bit
           self.utf8₋bytes₋idx += 1
           if followers >= 1 && self.utf8₋bytes₋idx < self.rendition.utf8₋bytes.count {
             self.maxfour[1] = self.rendition.utf8₋bytes[self.utf8₋bytes₋idx]
             self.utf8₋bytes₋idx += 1
           }
           if followers >= 2 && self.utf8₋bytes₋idx < self.rendition.utf8₋bytes.count {
             self.maxfour[2] = self.rendition.utf8₋bytes[self.utf8₋bytes₋idx]
             self.utf8₋bytes₋idx += 1
           }
           if followers >= 3 && self.utf8₋bytes₋idx < self.rendition.utf8₋bytes.count {
             self.maxfour[3] = self.rendition.utf8₋bytes[self.utf8₋bytes₋idx]
             self.utf8₋bytes₋idx += 1
           }
           let uc = Utf8ToUnicode(self.maxfour, Int64(followers) + 1)
           self.rendition.unicodes.append(uc)
           print("added \(uc)")
           if (uc == 0x0a) {
             self.rendition.linebreaks.append(self.rendition.unicodes.count - 1)
             print("and added linebreak")
           }
         }
       }
       DispatchQueue.main.async { self.minimumview.needsDisplay = true }
     }
     shell.commence(execute: "zsh", parameters: [], path₋exe: "/bin/")
   }
}

extension Windowcontroller { /* ⬷ keyboard input. */
   func keyput(_ uc: UInt32) {
     print("writing \(uc) to child")
     shell.slow₋write₋to₋child(uc)
     self.rendition.unicodes.append(uc)
     let uc₋count = self.rendition.unicodes.count
     let break₋count = self.rendition.linebreaks.count
     self.minimumview.needsDisplay = true
   }
   override func keyDown(with event: NSEvent) {
     if let characters = event.characters {
       for symbol: Character in characters {
         for possibly₋canonic in symbol.unicodeScalars {
           var uc: UInt32 = possibly₋canonic.value
           if uc == 0xd { uc = 0xa }
           keyput(uc)
         }
       }
     }
   }
}

