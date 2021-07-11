/*  􀴓􀲎 terms.swift | histories logged. */

import AppKit
import Metal

class Minimumview: NSView {
  
  override init(frame frameRect: NSRect) {
    print("minimumview-init")
    super.init(frame: frameRect)
    self.wantsLayer = true
    self.layerContentsRedrawPolicy = .onSetNeedsDisplay
    self.layerContentsPlacement = .scaleAxesIndependently
    self.composition.name = "Composition"
    DispatchQueue.main.asyncAfter(deadline: .now() + .seconds(1)) {
      let update = NSRect(x: 0, y: 0, width: self.frame.width, height: self.frame.height)
      print("setNeedsDisplay \(update)")
      self.setNeedsDisplay(update)
    }
    /* register(forDraggedTypes: [ NSFilenamesPboardType ]) */
  }
  
  required init?(coder: NSCoder) {
    fatalError("init(coder:) not implemented")
  }
  
  static let paper = NSColor(calibratedWhite: 0.95, alpha: 1.0), 
    paperborder = NSColor(calibratedWhite: 0.75, alpha: 1.0)
  static let cropmarks = NSColor(calibratedWhite: 0.70, alpha: 1.0)
  static let fine₋grid = NSColor(calibratedWhite: 0.92, alpha: 1.0), 
   coarse₋grid = NSColor(calibratedWhite: 0.88, alpha: 1.0)
  static let systemfont = NSFont.systemFont(ofSize: 30.0)
  static let textcolor = NSColor(named: NSColor.Name("primaryControlColor"))
  static let frame₋anfang = NSRect(x: 120.0, y: 50.0, width: 48.0, height: 48.0)
  let text₋attrs: [NSAttributedString.Key: Any] = [
    .foregroundColor: NSColor.orange.cgColor, 
    .font: NSFont(name: "Menlo", size: 14)!
  ]
  var rendered₋images = Dictionary<String, CGImage>()
  
  var y₋offset: CGFloat = 0.0 /* ⬷ visible rect, overdraw and underdraw. */
  var x₋offset: CGFloat = 0.0 /* ⬷ allows for horizontal scrolling including max line length in document. */
  
  let Operations₁ = DispatchQueue(label: "myops", attributes: .concurrent) /* ⬷ for visible work. */
  let Operations₂ = DispatchQueue(label: "myjobs" /* , attributes: .serial */) /* ⬷ for non-visible work. */
  /* ⬷ samgörande alt․ schemalaggda (▚). */
  
  var mouseIsOver: Bool = false /* ⬷ you should hit₋test this on init. */
  var hasMouseEntered: Bool = false /* ⬷ you should hit₋test this on init. */
  /* for context menu: func menuForEvent(event: NSEvent) -> NSMenu? {
   let popover = NSMenu(title: "")
   let item = NSMenuItem(title: "hello", action: "somethingelse:", keyEquivalent: "")
   item.target = self
   popover.addItem(item)
   return menu } with func somethingelse(menuItem: NSMenuItem) { } and not:
   popover.popUpMenuPositioningItem(nil, atLocation: NSMakePoint(), inView: sender) */
  
  func twopass₋and₋total₋height() -> CGFloat { return 100.0 }
  func twopass₋and₋O₍n₎₋total₋width() -> CGFloat { return 100.0 }
  
  func loupe₋pressed(points: [CGPoint]) { } /* ⬷ 􀤎. */
  func perspective₋pressed(point: [CGPoint]) { } /* ⬷ 􀢅􀢇􀌆􀒱􀎮􀆔􀊅􀟪􀋘􀱀􀙟􀘽􀆃=􀃌. */
  
  class Inexplanat { var explained = CAShapeLayer(); var symbols = CATextLayer() }
  typealias SEImageLayer = CALayer
  let textlayer = CATextLayer()
  var layers₋with₋images = Array<SEImageLayer>()
  var layers₋with₋realtime = Array<CAMetalLayer>()
  var vector₋layers = Array<CAShapeLayer>()
  var scribble₋layers = Array<Inexplanat>()
  let composition₋delegate = default₋Layerdelegate()
  let composition = CALayer() /* ⬷ alt․ CATransformLayer. */
  
  enum type₋of₋layer { case image; case simulation; case vector }
  enum anchor { case middle; case ul; case ll; case ur; case lr }
  
  func add₋rendition(layer₋type: type₋of₋layer, name: String, canvas₋initial: 
   NSPoint, canvas₋size: NSSize, origo₋relative₋superlayer: anchor) -> UUID {
    var ancestor: CALayer? = nil
    let identifier = UUID()
    switch layer₋type {
    case .image:
     let layer = SEImageLayer()
     layers₋with₋images.append(layer)
     ancestor = layer
    case .simulation:
     let layer = CAMetalLayer()
     layers₋with₋realtime.append(layer)
     ancestor = layer
    case .vector:
     let layer = CAShapeLayer()
     vector₋layers.append(layer)
     ancestor = layer
    } /* ⬷ note 'doublesided' defaults to true. */
    if let layer = ancestor {
      layer.frame = CGRect(x: 0, y: 0, width: canvas₋size.width, height: canvas₋size.height)
      switch origo₋relative₋superlayer {
      case .middle:
        layer.anchorPoint = CGPoint(x: 0.5, y: 0.5)
      case .ul:
        layer.anchorPoint = CGPoint(x: 0.0, y: 1.0)
      case .ll:
        layer.anchorPoint = CGPoint(x: 0.0, y: 0.0)
      case .ur:
        layer.anchorPoint = CGPoint(x: 1.0, y: 1.0)
      case .lr:
        layer.anchorPoint = CGPoint(x: 0.0, y: 1.0)
      }
      layer.transform = CATransform3DIdentity /* …and not CGAffineTransform.identity. */
      layer.name = name
      layer.isGeometryFlipped = true
      /* layer.shouldRasterize = false */
      /* layer.rasterizationScale = 2.0 */
      /* layer.autoresizingMask: CAAutoresizingMask = 
       [.kCALayerWidthSizable, .kCALayerHeightSizable] */
      composition.addSublayer(layer)
    }
    
    return identifier
    
  }
  
  enum instruction { case place; case base₋16₋encode; case utf₋8; case bezier; 
   case fill; case color₋select }
  typealias parameter₋tuple = (String, String, String, String)
  func assemble(_ op: instruction, params arguments: parameter₋tuple) {
  } /* 􀈍 */
  
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
      
      let string = "```\nlet x = 5\nprint(x)\n```"
      let text = NSAttributedString(string: string, attributes: text₋attrs)
      let framesetter = CTFramesetterCreateWithAttributedString(text)
      let textRange = CFRangeMake(0, text.length)
      let box = bounds.insetBy(dx: 16, dy: 16).offsetBy(dx: 16, dy: -16)
      let textContainerPath =  CGPath(rect: box.insetBy(dx: 8, dy: 8), transform: nil)
      let frame = CTFramesetterCreateFrame(framesetter, textRange, textContainerPath, nil)
      omgivning.textPosition = CGPoint(x: 8, y: 24)
      CTFrameDraw(frame,omgivning)
    }
    NSGraphicsContext.current = nil
    return omgivning.makeImage()
  }
  func reassign₋static₋rendition(_ layer: CALayer, static₋image: CGImage) {
    layer.contents = static₋image; /* ⬷ CGImageRef alternatively NSImage. */
    /* See 'CGImageSource.h'. */
  }
  func snapshot₋rendition() { let rect = NSRect()
    let repres: NSBitmapImageRep? = self.bitmapImageRepForCachingDisplay(in: rect)
    print("repres \(repres)")
  }
  func incorp₋rendition(layer₋type: type₋of₋layer, name: String, canvas₋initial: NSPoint, 
   canvas₋size: NSSize, origo₋relative₋superlayer: anchor) -> UUID {
    return UUID()
  }
  func apply₋ornaments() { let rect = NSRect() 
    let owner: Any = self
    let userdata: UnsafeMutableRawPointer? = nil
    let flag: Bool = true
    let tag: NSView.TrackingRectTag = self.addTrackingRect(rect, owner: self, 
     userData: userdata, assumeInside: flag)
    let local₋cursor: NSCursor = NSCursor.dragCopy
    self.addCursorRect(rect, cursor: local₋cursor)
    let trackingareas = {
      self.letgo₋ornaments()
      let opts: NSTrackingArea.Options = [.cursorUpdate, .mouseEnteredAndExited, .activeInKeyWindow]
      let area = NSTrackingArea(rect: self.bounds, options: opts, owner: self, userInfo: nil)
      self.addTrackingArea(area)
    }
  }
  func letgo₋ornaments() { for area in trackingAreas { self.removeTrackingArea(area) } }
  func hit₋test(point: CGPoint) -> CALayer? { return composition.hitTest(point) }
  
  /* translateRectsNeedingDisplayInRect */
  
  override var isOpaque: Bool { false }
  override var isFlipped: Bool { true }
  override var wantsUpdateLayer: Bool { true }
  override var preservesContentDuringLiveResize: Bool { true }
  /* override func setFrameSize() { super.setFrameSize(); if self.inLiveResize { 
     self.rectPreservedDuringLiveResize()
     var exposed₋rects: NSRect[4] var count: Int
     self.getRectsExposedDuringLiveResize:(&exposed₋rects, count: &count)
     for (int i=0; i<count; ++i) { NSRect r = rects[i]; [self setNeedsDisplayInRect:r]; }
   } else { self.setNeedDisplay(true) } */
  /* override var wantsDefaultClipping: Bool { false } */
  /* override var canDrawSubviewsIntoLayer: Bool { true } */
  /* override var layerUsesCoreImageFilters: Bool { true } */
  /* backgroundFilters, composingFilters and contentFilters. */
  
  override func makeBackingLayer() -> CALayer {
    composition.delegate = self.composition₋delegate
    composition.needsDisplayOnBoundsChange = true
    
    /* 􀑆 */
    /* 𐤟𐤟𐤟 */
    /* 􀞷 */
    
    return composition } /* ⬷ 𝘤𝘧․ against var layer: NSView.CALayer. */
  override func viewWillMove(toWindow: NSWindow?) {
    print("viewWillMoveToWindow")
    super.viewWillMove(toWindow: window) }
  override func viewWillMove(toSuperview: NSView?) {
    print("viewWillMoveToSuperview")
    super.viewWillMove(toSuperview: toSuperview) }
  override func updateLayer() {
    print("updateLayer")
    super.updateLayer()
    guard let ctx = NSGraphicsContext.current?.cgContext else { return }
    let path = NSBezierPath()
    path.move(to: NSPoint(x: 0, y: 0))
    path.line(to: NSPoint(x: 10, y: 10))
    path.stroke()
  }
  
  override func draw(_ dirty: CGRect) { print("draw-rect: \(dirty)") 
    
    guard let omgivning = NSGraphicsContext.current?.cgContext else { return }
    
    print("self.frame now is \(self.frame)")
    
    /* a small drawing-machine: */
    
    let setup₋coordinates = {
      let bounds = self.bounds
      let x₋form = NSAffineTransform.init() /* ⬷ identity matrix, not the contexts' matrix. */
      /* ⬷ error: 'transform' has been replaced by 'init'. */
      x₋form.translateX(by: 0.0, yBy: bounds.size.height)
      x₋form.scaleX(by: 1.0, yBy: -1.0)
      x₋form.concat() /* ⬷ updates the current cgContext. */
    }
    let draw₋pristine = {
     let bounds = NSRect(x: 10.0, y: 12.0, width: 400.0, height: 400.0)
     let inner = bounds.insetBy(dx: 20.0, dy: 20.0)
     omgivning.setFillColor(red: 0.0, green: 1.0, blue: 0.0, alpha: 1.0)
     omgivning.fillEllipse(in: inner)
     let anfang = NSBezierPath(anfang: "A", font: Minimumview.systemfont, frame: Minimumview.frame₋anfang)
     anfang.stroke()
    }
    /* let render₋verticalrun = { }
    let initiate₋onelinerun = { }
    let initiate₋layerplacement = { }
    let initiate₋layertransfer = { /* (area: NSRect) in */ }
    let arrange₋image = { }
    let placeimage = { (url: URL, rect: CGRect?) in 
      self.Operations₁.async {
        /* let pdfData: NSData = printingMapView.dataWithPDFInsideRect(frame)
        let image: NSImage = NSImage(withData: pdfData)
        image.setSize(size) */
        if let oneimage = NSImage(contentsOf: url) { /* ⬷ CALayers contents can directly be feed with NSImage. */
          var docrect: CGRect = NSRect(x: 0, y: 0, width: oneimage.size.width, height: oneimage.size.height)
          let oneref: CGImage? = oneimage.cgImage(forProposedRect: &docrect, context: nil, hints: nil)
          if let theref = oneref {
            DispatchQueue.main.async { /* images += theref */
              self.setNeedsDisplay(docrect)
            } /* ⬷ a serial queue and 'the main thread'. */
          }
        }
      }
    } / * light and dark appearances. */
    
    /* let intersection₋non₋empty = { (area: NSRect) in }
    let initiate₋imagedraw = { }
    let initiate₋vectordraw = { (area: NSRect, visible: NSRect) in } */
    
    setup₋coordinates()
    draw₋pristine()
    
    /* for i in 0..<non₋kernel₋images.count { 
     non₋kernel₋images[i].drawInRect(self.imageRect) } */
    
    var count=0; var rects: UnsafePointer<NSRect>?
    getRectsBeingDrawn(&rects, count: &count)
    if let rects = rects { for i in 0..<count { let rect = rects[i] 
      print("rect being drawn \(rect)")
      /* let intersect = NSIntersectionRect(error₋bounds, rect)
      if NSIsEmptyRect(intersect) {
        if intersection₋non₋empty(intersect) {
          /* drawing code for object */
        }
    } */ } }
    
    super.draw(dirty)
  }
  
  override func enterFullScreenMode(_ screen: NSScreen, withOptions options: 
    [NSView.FullScreenModeOptionKey : Any]? = nil) -> Bool { return false }
  override func exitFullScreenMode(options: [NSView.FullScreenModeOptionKey : Any]? = nil) { }
  
  override func viewWillStartLiveResize() { print("viewWillStartLiveResize") 
    super.viewWillStartLiveResize() }
  override func viewDidEndLiveResize() { print("viewDidEndLiveResize") 
    super.viewDidEndLiveResize() }
  override func viewDidChangeEffectiveAppearance() {
    print("viewDidChangeEffectiveAppearance")
    let all = NSRect(x: 0, y: 0, width: frame.width, height: frame.height)
    self.setNeedsDisplay(all) /* ⬷ c𝘧․ NSView.visibleRect. */
  }
  
  func viewDidUpdateTrackingAreas() { } /* NSViewDidUpdateTrackingAreasNotification */
  func viewGlobalFrameDidChange() { } /* NSViewGlobalFrameDidChangeNotification */
  func viewBoundsDidChange() { } /* NSViewBoundsDidChangeNotification */
  func viewFrameDidChange() { } /* NSViewFrameDidChangeNotification */
  
}

class Viewcontroller: NSViewController {
  
  init() { print("viewcontroller-init"); super.init(nibName: nil, bundle: nil) }
  
  required init?(coder: NSCoder) { fatalError("init(coder:) has not been implemented") }
  
  override func loadView() { print("Loading View") 
    let initial₋placement = NSPoint(x: 0, y: 0) /* ⬷ unused. */
    let initial₋rect = NSSize(width: 501, height: 502) /* ⬷ construe and merged later. */
    let frame = NSRect(origin: initial₋placement, size: initial₋rect)
    let visualeffect = NSVisualEffectView(frame: frame)
    visualeffect.translatesAutoresizingMaskIntoConstraints = false
    visualeffect.blendingMode = .behindWindow
    visualeffect.state = .active
    /* visualeffect.layer?.cornerRadius = 16.0 */
    /* visualeffect.maskImage = NSImage(data: Data(contentsOf: url)) /​* ⬷ '130px-Cross-Pattee-Heraldry.png'. */
    self.view = visualeffect
    let material = Minimumview(frame: frame)
    /* material.acceptsTouchEvents = true */
    material.allowedTouchTypes = [.indirect] /* ⬷ ipad = .direct */
    self.view.addSubview(material)
    NSLayoutConstraint.activate([
     material.leadingAnchor.constraint(greaterThanOrEqualTo: visualeffect.safeAreaLayoutGuide.leadingAnchor, constant: 20), 
     material.trailingAnchor.constraint(greaterThanOrEqualTo: visualeffect.safeAreaLayoutGuide.trailingAnchor, constant: 20), 
     material.topAnchor.constraint(greaterThanOrEqualTo: visualeffect.safeAreaLayoutGuide.topAnchor, constant: 20), 
     material.bottomAnchor.constraint(greaterThanOrEqualTo: visualeffect.safeAreaLayoutGuide.bottomAnchor, constant: 20)
    ])
    
   /* let header: NSAttributedString = minimumview.pageHeader
    let footer: NSAttributedString = minimumview.pageFooter
    let jobname: String = minimumview.printJobTitle */
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
  
  var minimumview: Minimumview { get { self.view.subviews[0] as! Minimumview } }
  
  struct Sample { var position: NSPoint; var pressure: Double }
  var tracklines = Dictionary<NSView.Trek, Array<Sample>>() /* ⬷ c𝘧․ preskriptionstid. */
  
  override var representedObject: Any? {
    didSet { /* update the view if already loaded. */ }
  }
  
  /* Also keyed 'run-block' and 'load-block'. In terminal implicit 'run-block'. */
  
  override var acceptsFirstResponder: Bool { true }
  
  override func touchesBegan(with event: NSEvent) {
    let ovals: Set<NSTouch> = event.touches(matching: .began, in: minimumview)
    for oval in ovals {
      let identity = oval.identity
      print("tip-start \(identity)")
    }
  }
  override func touchesMoved(with event: NSEvent) {
    let ovals: Set<NSTouch> = event.touches(matching: .moved, in: minimumview)
    for oval in ovals {
      let identity = oval.identity
      let normalized = oval.normalizedPosition
      /* composition₋delegates.updateValue(base₋delegate, forKey: base₋identifier)  */
      print("tip-moved at \(normalized)")
    }
  }
  override func touchesEnded(with event: NSEvent) {
    let ovals: Set<NSTouch> = event.touches(matching: .ended, in: minimumview)
    for oval in ovals {
      let identity = oval.identity
      print("tip-ended \(identity)")
    }
  }
  override func touchesCancelled(with event: NSEvent) {
    let ovals: Set<NSTouch> = event.touches(matching: .cancelled, in: minimumview)
    for oval in ovals {
      let identity = oval.identity
      print("tip-cancelled \(identity)")
    }
  }
  
  override func pressureChange(with event: NSEvent) {
    let pressure = event.pressure
    let location₁ = event.locationInWindow
    /* let location₂ = self.superview.convertPoint(location₁, fromView: nil) */
    print("pressure is \(pressure) at \(location₁)")
  }
  
  override func cursorUpdate(with event: NSEvent) { print("cursorUpdate") 
    /* NSCursor.arrowCursor.set */
    super.cursorUpdate(with: event)
  }
  
  override func mouseExited(with event: NSEvent) { print("mouseexited") 
    super.mouseExited(with: event)
  }
  
  override func mouseEntered(with event: NSEvent) { print("mouseentered") 
    super.mouseEntered(with: event)
  }
  
  override func noResponder(for: Selector) { print("no responder") }
  
  func addScribblelayer(_ sender: AnyObject)
  {
     print("Adding scribbleview")
  }
  
  static func incorporate₋scribble₋in₋menu(include yes: Bool) {
    guard let viewmenu = NSApplication.shared.mainMenu.items[5] else { return }
    if yes == true && viewmenu.submenu.action != #selector(addScribblelayer(_:)) {
      let item = NSMenuItem(title: "Add Scribble...", target: self, 
       action: #selector(addScribblelayer(_:)), keyEquivalent: "n", 
       modifier: [NSEvent.ModifierFlags.shift, NSEvent.ModifierFlags.command]
      viewmenu.submenu?.items.insert(item), at: 2)
    }
    if yes == false && viewmenu.submenu.action != #selector(addScribblelayer(_:)) {
      viewmenu.submenu?.items.remove(at: 2)
    }
  }
  
  @objc func validateMenuItem(_ menuItem: NSMenuItem) -> Bool {
    print("validate menu for view")
    incorporate₋scribble₋in₋menu(include: true)
    guard let window = self.minimumview.window else { return }
    return window.validateMenuItem(menuItem)
  }
  
}

class Windowcontroller: NSWindowController {
   
   let viewctrl = Viewcontroller()
   var shell = Inter₋act₋and₋inte₋r₋u₋p₋t()
   var recorder = UndoManager() /* ⬷ duplicate undoManager in NSResponder. */
   
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
   
   func coroutine₋keyput₋in₋child(writer: FileHandle) async -> Int { var exitstatus=0 
     /* for try await line in input₋handle.bytes.lines { print(line) } */
     return exitstatus
   } /* ⬷ a coroutine may suspend at anytime. */
   /* 'löper samtidigt' ≢ async a․𝘬․a 'ombesörjd samt stimuli' */
   /* async-let=spawn and await=co_await-after∧join */
   
   override func windowDidLoad() { print("windowDidLoad"); reloadUi() 
     NotificationCenter.receive(.preferences₋changed, 
      instance: self, selector: #selector(reloadUi))
     let out = { (material: Data) in 
      let text = String(bytes: material, encoding: String.Encoding.utf8)
      print("message: \(String(describing: text))") }
     /* let y = shell.occurrent₋spawn(execute: "ls", parameters: ["-l", "-a"], 
      in: coroutine₋keyput, out: out)
     if y != 0 { print("unable to spawn") } */
   }
   
   func windowWillReturnUndoManager(_ window: NSWindow) -> UndoManager? { return recorder }
   
   @objc private func reloadUi() { print("reloadUi") 
     
     if #available(OSX 10.14, *) {
       if NSApp.effectiveAppearance.name == .darkAqua { return }
     }
     
     /* window?.backgroundColor = theme.background */
     
     // if theme.background.isDark {
       window?.appearance = NSAppearance(named: .darkAqua)
     // } else {
       window?.appearance = NSAppearance(named: .aqua)
     // }
   }
   
   @objc func validateMenuItem(_ menuItem: NSMenuItem) -> Bool {
     print("validate-window-menu")
     return NSApplication.shared.validateMenuItem(menuItem)
   }
   
} /* ⬷ c𝘧․ Windowcontroller and Ieee754-Opt. */

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
   
   var controller: Viewcontroller { get { self.contentViewController! as! Viewcontroller } }
   
   var shift=false, ctrl=false, opt=false, cmd=false
   
   override func flagsChanged(with event: NSEvent) { print("flagsChanged") 
     let modifs: NSEvent.ModifierFlags = event.modifierFlags
     shift = modifs.contains(.shift)
     ctrl = modifs.contains(.control)
     opt = modifs.contains(.option)
     cmd = modifs.contains(.command)
   } /* ⬷ 'OptionSet', not a generic …. */
   
   override func performKeyEquivalent(with event: NSEvent) -> Bool {
     print("performKeyEquivalent")
     return super.performKeyEquivalent(with: event)
   }
   
   override func keyDown(with event: NSEvent) {
     super.keyDown(with: event)
     print("keydown \(event.keyCode)")
     print("keydown \(String(describing: event.characters))")
     let description = event.modifierFlags.rawValue.description
     print("modifier \(String(describing: description))")
     let view = controller.view.subviews[0]
     let minimumview = view as! Minimumview
     if let characters = event.characters {
       for symbol: Character in characters {
         print("utf8 (\(symbol.utf8)): ", terminator: "")
         symbol.utf8.forEach { byte in print("\(byte) ", terminator: "") }
         print("\nunicodes \(symbol.unicodeScalars)")
         for possibly₋canonical in symbol.unicodeScalars { /* ⬷ UInt32. */
           let possibly₋canonical₂ = 
  Int(truncatingIfNeeded: possibly₋canonical.value)
           switch possibly₋canonical₂ {
           case NSDeleteFunctionKey:
             print("deleteKeyDown")
           case NSInsertFunctionKey:
             print("insertKeyDown")
           case NSClearLineFunctionKey:
             print("clearlineKeyDown")
           case NSClearDisplayFunctionKey:
             print("cleardisplayKeyDown")
           case NSModeSwitchFunctionKey:
             print("modeSwitchKeyDown")
           case NSPageUpFunctionKey:
             print("pageupKeyDown")
           case NSPageDownFunctionKey:
             print("pagedownKeyDown")
           case NSPrintScreenFunctionKey:
             print("printScreenKeyDown")
           case NSBreakFunctionKey:
             print("breakKeyDown")
           case NSStopFunctionKey:
             print("stopKeyDown")
           case NSResetFunctionKey:
             print("resetKeyDown")
           case NSPrintFunctionKey:
             print("printKeyDown")
           case NSInsertCharFunctionKey:
             print("insertCharKeyDown")
           case NSUndoFunctionKey:
             print("undoKeyDown")
           case NSRedoFunctionKey:
             print("redoKeyDown")
           case 0x0020: quicklook()
           default:
             print("keydown default end")
           }
         }
       }
     }
   } /* ⬷ String, Character, Unicode and StaticString. */
   
}

extension Minimumwindow { /* ⬷ typed 'irreversible' and 'undoable'. */
  
  var minimumview: Minimumview { controller.minimumview }
  
  func quicklook() {
    minimumview.Operations₂.async { DispatchQueue.main.async {
    } }
  }
  
  func explain₋definition() {
    minimumview.Operations₂.async { DispatchQueue.main.async {
      let attribed = NSAttributedString(string: "Hello world")
      let baseline₋origin = NSPoint()
      self.minimumview.showDefinition(for: attribed, at: baseline₋origin)
      let target₋range = NSRange()
      let options = [NSView.DefinitionOptionKey:Any]()
      let baselineOriginProvider = { (adjustedRange: NSRange) -> NSPoint in return NSPoint(x: 0, y: 0) }
      self.minimumview.showDefinition(for: attribed, range: target₋range, options: options, 
        baselineOriginProvider: baselineOriginProvider)
    } }
  }
  
  func start₋find₋expression₋alt₋phrase() {
    minimumview.Operations₂.async { DispatchQueue.main.async {
      /* minimumview.drawingFindIndicator = true */
      /* NotificationCenter.send() */
    } }
  }
  
  func pause₋scroll() {
    minimumview.Operations₂.async { DispatchQueue.main.async {
    } }
  }
  
  func unpause₋scroll() {
    minimumview.Operations₂.async { DispatchQueue.main.async {
    } }
  }
  
  func toggle₋pause₋auto₋scroll(enabled: Bool) {
    minimumview.Operations₂.async { DispatchQueue.main.async {
    } }
  }
  
}


