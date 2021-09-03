/*  􀴓􀲎 terms.swift | histories logged. */

import AppKit
import Metal /* ⬷ alt․ AppKit + Metal. */

class Minimumview: NSView {
  
  override init(frame frameRect: NSRect) {
    print("minimumview-init")
    super.init(frame: frameRect)
    self.wantsLayer = true
    let later₋future: DispatchTime = .now() + .seconds(1)
    DispatchQueue.main.asyncAfter(deadline: later₋future) {
      let frame₋update = NSRect(x: 0, y: 0, width: self.frame.width, 
       height: self.frame.height)
      print("setNeedsDisplay \(frame₋update)")
      self.setNeedsDisplay(frame₋update)
    }
    /* init₋for₋dropping(NSFilenamesPboardType) */
  }
  
  required init?(coder: NSCoder) {
    fatalError("init(coder:) not implemented")
  }
  
  static let paper = NSColor(calibratedWhite: 0.95, alpha: 1.0), 
    paperborder = NSColor(calibratedWhite: 0.75, alpha: 1.0)
  static let cropmarks = NSColor(calibratedWhite: 0.70, alpha: 1.0)
  static let fine₋grid = NSColor(calibratedWhite: 0.92, alpha: 1.0), 
   coarse₋grid = NSColor(calibratedWhite: 0.88, alpha: 1.0)
  static let systemfont = NSFont.systemFont(ofSize: 30.0), 
   textfont = NSFont(name: "SF Mono", size: 9)
  static let textcolor = NSColor(named: NSColor.Name("primaryControlColor"))
  static let frame₋anfang = NSRect(x: 120.0, y: 50.0, width: 48.0, height: 48.0)
  
  var default₋textattrs: [NSAttributedString.Key: Any] {
    get {
      guard let font = Minimumview.textfont else { return [:] }
      guard let fg₋color = Minimumview.textcolor else { return [:] }
      return [.font: font, .foregroundColor: fg₋color.cgColor]
    }
  }
  
  let Operations₁ = DispatchQueue(label: "myops", attributes: .concurrent) /* ⬷ for visible work. */
  let Operations₂ = DispatchQueue(label: "myjobs" /* , attributes: .serial */) /* ⬷ for non-visible work. */
  /* ⬷ samgörande alt․ schemalaggda (▚) also four-queues for bolted 'gammalt-and-nytt': 
   mypresentation and myevaluation. */
  
  var rendered₋named₋images = Dictionary<UUID,CGImage>()
  
  struct /* not₋actor */ minimum₋collection {
    let text = CATextLayer()
    var layers₋with₋realtime = Dictionary<UUID,CAMetalLayer>()
    var layers₋with₋illustrations = Dictionary<UUID,CALayer>()
    var scribbles = Dictionary<UUID,Feedback>()
    let composition = CALayer() /* ⬷ a․𝘬․a composition₋with₋scribble. */
  }
  
  var collection = minimum₋collection()
  let composition₋delegate = Compositiondelegate()
  
  class Feedback { var explained=CAShapeLayer(); var symbols=CATextLayer() } /* ⬷ a․𝘬․a Inexplanat. */
  
  func total₋twopass₋and₋height() -> CGFloat { return 100.0 }
  func total₋twopass₋and₋width₋in₋O₍n₎() -> CGFloat { return 100.0 }
  
  var y₋offset: CGFloat = 0.0 /* ⬷ visible rect, overdraw and underdraw. */
  var x₋offset: CGFloat = 0.0 /* ⬷ allows for horizontal scrolling including max line length in document. */
  
  var pointerIsOver: Bool = false /* ⬷ you should hit₋test this on init. */
  var hasPointerEntered: Bool = false /* ⬷ you should hit₋test this on init. */
  
  enum type₋of₋layer { case simulation; case illustration }
  enum anchor { case middle; case ul; case ll; case ur; case lr }
  
  func hit₋test(point: CGPoint) -> CALayer? { return collection.composition.hitTest(point) }
  
  func letgo₋all₋ornaments() { for area in trackingAreas { self.removeTrackingArea(area) } }
  
  func apply₋ornaments() {
    self.letgo₋all₋ornaments()
    let rect = NSRect(x: 10, y: 10, width: 100, height: 100)
    let local₋cursor: NSCursor = NSCursor.dragCopy
    self.addCursorRect(rect, cursor: local₋cursor)
    let strategy₁ = {
      let userdata: UnsafeMutableRawPointer? = nil
      let _ /* tag */: NSView.TrackingRectTag = self.addTrackingRect(rect, owner: self, 
       userData: userdata, assumeInside: true)
       self.updateTrackingAreas()
    }
/*    let _ /* strategy₂ */ = { tracking₋bounds: NSRect in 
      let opts: NSTrackingArea.Options = [.cursorUpdate, .mouseEnteredAndExited, .activeInKeyWindow]
      /* let opts = [NSTrackingArea.Options.activeAlways, NSTrackingArea.Options.mouseMoved, NSTrackingArea.Options.mouseEnteredAndExited] */
      let area = NSTrackingArea(rect: tracking₋bounds, options: opts, owner: self, userInfo: nil)
      self.addTrackingArea(area)
    } */
    strategy₁()
  }
  
  let post₋init₋layer = { (layer: inout CALayer) -> Void in 
    layer.transform = CATransform3DIdentity /* …and not CGAffineTransform.identity. */
    layer.contentsScale = 2.0 /* for retina. */
    layer.backgroundColor = NSColor.clear.cgColor
    layer.contentsGravity = .center
    layer.contentsCenter = CGRect(x: 0.0, y: 0.0, width: 10.0, height: 10.0)
    layer.contentsFormat = CALayerContentsFormat.RGBA8Uint
    layer.isOpaque = false
    layer.needsDisplayOnBoundsChange = true
    layer.drawsAsynchronously = true
  }
  
  func add₋rendition₋layer(layer₋type: type₋of₋layer, name: String, canvas₋initial: 
   NSPoint, canvas₋size: NSSize, origo₋relative₋superlayer: anchor) -> UUID {
    var sublayer: CALayer? = nil
    let ident = UUID()
    switch layer₋type {
    case .simulation:
     let layer = CAMetalLayer()
     collection.layers₋with₋realtime.updateValue(layer, forKey: ident)
     sublayer = layer
    case .illustration: /* ₋and₋photography. */
     let layer = CALayer()
     collection.layers₋with₋illustrations.updateValue(layer, forKey: ident)
     sublayer = layer
    } /* ⬷ note 'doublesided' defaults to true. */
    if var addition = sublayer {
      addition.frame = CGRect(x: canvas₋initial.x, y: canvas₋initial.y, width: canvas₋size.width, height: canvas₋size.height)
      switch origo₋relative₋superlayer {
      case .middle:
        addition.anchorPoint = CGPoint(x: 0.5, y: 0.5)
      case .ul:
        addition.anchorPoint = CGPoint(x: 0.0, y: 1.0)
      case .ll:
        addition.anchorPoint = CGPoint(x: 0.0, y: 0.0)
      case .ur:
        addition.anchorPoint = CGPoint(x: 1.0, y: 1.0)
      case .lr:
        addition.anchorPoint = CGPoint(x: 0.0, y: 1.0)
      }
      addition.name = name
      post₋init₋layer(&addition)
      addition.isGeometryFlipped = true
      collection.composition.addSublayer(addition)
      /* setNeedsLayout() setNeedsDisplay() setNeedsDisplayInRect(r: CGRect) */
    }
    return ident
  } /* ⬷ a․𝘬․a incorp₋rendition. */
  
  override var isOpaque: Bool { false }
  override var isFlipped: Bool { true }
  override var wantsUpdateLayer: Bool { true }
  override var preservesContentDuringLiveResize: Bool { true }
  override func setFrameSize(_ newSize: NSSize) {
    super.setFrameSize(newSize)
    if self.inLiveResize {
      let r: NSRect = self.rectPreservedDuringLiveResize
      print("rectPreservedDuringLiveResize: \(r)")
      var count: Int = 0; let exposed: (NSRect,NSRect,NSRect,NSRect) =
       (NSZeroRect,NSZeroRect,NSZeroRect,NSZeroRect)
      typealias Pr = UnsafeMutablePointer<NSRect>
      let exposed₂: Pr = unsafeBitCast(exposed, to: Pr.self)
      self.getRectsExposedDuringLiveResize(exposed₂, count: &count)
      if count >= 1 { self.setNeedsDisplay(exposed.0) }
      if count >= 2 { self.setNeedsDisplay(exposed.1) }
      if count >= 3 { self.setNeedsDisplay(exposed.2) }
      if count >= 4 { self.setNeedsDisplay(exposed.3) }
     } else { self.needsDisplay = true }
   }
  
  /* 􀑆 */ /* 𐤟𐤟𐤟 */
  /* override var wantsDefaultClipping: Bool { false } */
  /* override var canDrawSubviewsIntoLayer: Bool { true } */
  /* override var layerUsesCoreImageFilters: Bool { true } */
  /* backgroundFilters, composingFilters and contentFilters. */
  /* 􀞷 */
  
  override func makeBackingLayer() -> CALayer {
    let composition = collection.composition
    composition.name = "Composition"
    composition.delegate = self.composition₋delegate
    self.layerContentsRedrawPolicy = NSView.LayerContentsRedrawPolicy.duringViewResize
    self.layerContentsPlacement = .scaleAxesIndependently
    composition.layoutManager = CAConstraintLayoutManager()
    composition.needsDisplayOnBoundsChange = true
   /* composition.autoresizingMask: CAAutoresizingMask = 
     [.kCALayerWidthSizable, .kCALayerHeightSizable] */
    composition.backgroundColor = Minimumview.paper.cgColor
    composition.borderColor = Minimumview.paperborder.cgColor
    composition.borderWidth = 0.5
    return composition }
  override func viewWillMove(toWindow: NSWindow?) {
    print("viewWillMoveToWindow")
    super.viewWillMove(toWindow: window) }
  override func viewWillMove(toSuperview: NSView?) {
    print("viewWillMoveToSuperview")
    super.viewWillMove(toSuperview: toSuperview) }
  override func viewWillStartLiveResize() { print("viewWillStartLiveResize") 
    super.viewWillStartLiveResize() }
  override func viewDidEndLiveResize() { print("viewDidEndLiveResize") 
    super.viewDidEndLiveResize() }
  override func viewDidChangeEffectiveAppearance() { print("viewDidChangeEffectiveAppearance") 
    let all = NSRect(x: 0, y: 0, width: frame.width, height: frame.height)
    self.setNeedsDisplay(all) /* ⬷ c𝘧․ NSView.visibleRect. */ }
  override func enterFullScreenMode(_ screen: NSScreen, withOptions options: 
      [NSView.FullScreenModeOptionKey : Any]? = nil) -> Bool { return false }
  override func exitFullScreenMode(options: [NSView.FullScreenModeOptionKey : Any]? = nil) { }
    func viewDidUpdateTrackingAreas() { } /* NSViewDidUpdateTrackingAreasNotification */
    func viewGlobalFrameDidChange() { } /* NSViewGlobalFrameDidChangeNotification */
  func viewBoundsDidChange() { } /* NSViewBoundsDidChangeNotification */
  func viewFrameDidChange() { } /* NSViewFrameDidChangeNotification */
  override func updateLayer() {
    print("updateLayer")
    super.updateLayer()
    guard let _ /* ctx */ = NSGraphicsContext.current?.cgContext else { return }
    let path = NSBezierPath()
    path.move(to: NSPoint(x: 0, y: 0))
    path.line(to: NSPoint(x: 10, y: 10))
    path.stroke()
  }
}

extension Minimumview { /* ⬷ minimum and illustrations. */
  
   func render₋𝟾𝟹(text: String, width: Double, height: Double, ctx: inout CGContext) {
     let textattrs = default₋textattrs
     let attrtext = NSAttributedString(string: text, attributes: textattrs)
     let framesetter = CTFramesetterCreateWithAttributedString(attrtext)
     let symbols = CFRangeMake(0,attrtext.length)
     let box = bounds.insetBy(dx: 16, dy: 16).offsetBy(dx: 16, dy: -16)
     let textpath = CGPath(rect: box.insetBy(dx: 8, dy: 8), transform: nil)
     let frame = CTFramesetterCreateFrame(framesetter,symbols,textpath,nil)
     ctx.textPosition = CGPoint(x: 8, y: 24)
     CTFrameDraw(frame,ctx)
   }
  
  func render(illusts: Artwork₋swift..., topLeftNextBottom: NSEdgeInsets, columns: Int) {
    
    print("render \(columns) columns, inset \(topLeftNextBottom) with \(illusts)")
    
    let machine = Drawings₁()
    var parent₋cursor₋X=topLeftNextBottom.left
    var parent₋cursor₋Y=topLeftNextBottom.top
    var max₋height=0.0
    
    for (idx,figure) in illusts.enumerated() { /* ⬷ a․𝘬․a figures. */
      var size = CGSize(width: 0.0, height: 0.0); var name: String = ""
      do {
        try figure.text.withUTF8 { fromwire₋utf8 /* UnsafeBufferPointer<UInt8> */ in 
          let utf8₋material = fromwire₋utf8.baseAddress! as? UnsafeMutablePointer<UInt8> 
          let layer: CALayer = try /* await */ machine.interpret(bytes: fromwire₋utf8.count, 
           figure₋utf8: utf8₋material!, size: &size, name: &name)
          layer.frame = NSRect(x: parent₋cursor₋X, y: parent₋cursor₋Y, width: size.width, height: size.height)
          max₋height = max(layer.frame.height,max₋height)
          layer.name = name
          let column = (idx + 1) % columns
          if column == 0 {
            parent₋cursor₋X = topLeftNextBottom.left
            parent₋cursor₋Y += max₋height
            max₋height = 0.0
          }
          else { parent₋cursor₋X = size.width + topLeftNextBottom.right }
          
          let ident = UUID()
          collection.layers₋with₋illustrations.updateValue(layer, forKey: ident)
          collection.composition.addSublayer(layer)
        }
      } catch _ /* Drawings₁.Anomality.Rendition */ { print("render: exception") }
    }
    
  }
  
}

extension Minimumview {
  
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
}

extension Minimumview {
  func snapshot₋rendition() -> NSBitmapImageRep? { let rect = collection.text.frame 
    let bitmap: NSBitmapImageRep? = self.bitmapImageRepForCachingDisplay(in: rect)
    return bitmap } /* bitmap.planar, bitmap.samplesPerPixels, ... */
}

class Compositiondelegate: NSObject, CALayerDelegate {
  class Action: CAAction {
    func run(forKey event: String, object anObject: Any, 
     arguments: [AnyHashable : Any]?) { print("run \(event)") }
  }
  func optname(_ layer: CALayer) -> String { return layer.name ?? "no-name" }
  func display(_ layer: CALayer) { print("display \(optname(layer))") }
  func draw(_ layer: CALayer, in ctx: CGContext) { print("draw \(optname(layer))") 
    /* CGContextBeginTransparencyLayer(ns₋omgivning, nil)
    CGContextEndTransparencyLayer(ns₋omgivning) */
  }
  func layerWillDraw(_ layer: CALayer) { print("layerWillDraw \(optname(layer))") }
  func layoutSublayers(of layer: CALayer) { print("layoutSublayers \(optname(layer))") }
  func action(for layer: CALayer, forKey event: String) -> CAAction? {
    print("action \(optname(layer))")
    return Action() }
}

extension Minimumview {
  func loupe₋overlayed(_ sender: AnyObject) {
    /* let bounds = CGContextConvertRectToDeviceSpace() */
    /* composition.minificationFilter = CALayer.trilinear 
    composition.magnificationFilter = CALayer.trilinear */
    /* CALayerContentsFilter */
  } /* ⬷ protocol-􀤎. */
  enum Perspective { case undo; case redo; case hidden₋detailed }
  func perspective₋toggled(_ sender: AnyObject) { } /* ⬷ 􀢅􀢇􀌆􀒱􀎮􀆔􀊅􀟪􀋘􀱀􀙟􀘽􀆃=􀃌. */
}

extension Viewcontroller { /* ⬷ trackpad. */
  override func touchesBegan(with event: NSEvent) {
    trackpad.log₋rectangle(with: event, view: minimumview, initial: true)
    super.touchesBegan(with: event) }
  override func touchesMoved(with event: NSEvent) {
    trackpad.log₋rectangle(with: event, view: minimumview, initial: false)
    /* self.translateRectsNeedingDisplayInRect(NSRect(), by: NSSize()) */
    super.touchesMoved(with: event) }
  override func touchesEnded(with event: NSEvent) {
    trackpad.ended(with: event, view: minimumview)
    super.touchesEnded(with: event) }
  override func touchesCancelled(with event: NSEvent) {
    trackpad.cancelled(with: event, view: minimumview)
    super.touchesCancelled(with: event) }
  override func mouseExited(with event: NSEvent) { print("mouseexited") 
    trackpad.exited(with: event, in: self.view)
    super.mouseExited(with: event) }
  override func mouseEntered(with event: NSEvent) { print("mouseentered") 
    trackpad.entered(with: event, in: self.view)
    super.mouseEntered(with: event) }
  override func pressureChange(with event: NSEvent) { 
    trackpad.pressure(with: event)
    super.pressureChange(with: event)
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
  
  var trackpad = Trackpad()
  
  override var representedObject: Any? {
    didSet { /* update the view if already loaded. */ }
  }
  
  /* Also keyed 'run-block' and 'load-block'. In terminal implicit 'run-block'. */
  
  override var acceptsFirstResponder: Bool { true }
  
  override func cursorUpdate(with event: NSEvent) { print("cursorUpdate") 
    /* NSCursor.arrowCursor.set */
    /* NSCursor.dragCopyCursor.set */
    super.cursorUpdate(with: event)
  }
  
  override func noResponder(for: Selector) { print("no responder") }
  
  @objc 
  func addScribblelayer(_ sender: AnyObject)
  {
     print("Adding scribbleview")
  }
  
  static func incorporate₋scribble₋in₋menu(include yes: Bool) {
    guard let viewmenu: NSMenuItem = NSApplication.shared.mainMenu?.items[5] else { return }
    if yes == true && viewmenu.submenu?.items[1].action != #selector(addScribblelayer(_:)) {
      let item = NSMenuItem(title: "Add Scribble...", target: self, 
       action: #selector(addScribblelayer(_:)), keyEquivalent: "n", 
       modifier: [NSEvent.ModifierFlags.shift, NSEvent.ModifierFlags.command])
      viewmenu.submenu?.items.insert(item, at: 2)
    }
    if yes == false && viewmenu.submenu?.items[1].action == #selector(addScribblelayer(_:)) {
      viewmenu.submenu?.items.remove(at: 2)
    }
  }
  
  @objc func validateMenuItem(_ menuItem: NSMenuItem) -> Bool {
    print("validate menu for view")
    Viewcontroller.incorporate₋scribble₋in₋menu(include: true)
    guard let window = self.minimumview.window else { return false }
    return window.validateMenuItem(menuItem)
  }
  
}

class Windowcontroller: NSWindowController {
   
   let viewctrl = Viewcontroller()
   var shell = Inter₋act₋and₋inte₋r₋u₋p₋t()
   var recorder = UndoManager() /* ⬷ duplicate undo-manager in NSResponder. */
   
   /* CAAction: func run(forKey event: String, object anObject: Any, 
    arguments dict: [AnyHashable : Any]?) { } */
   
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
   
   func coroutine₋keyput₋in₋child(writer: FileHandle) async /* a.k.a hypotes. */ -> Int { var exitstatus=0 
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
     /* let absorb₋sponge = event.pressure */
     let description = event.modifierFlags.rawValue.description
     print("modifier \(String(describing: description))")
     let view = controller.view.subviews[0]
     let minimumview = view as! Minimumview
     if let characters = event.characters {
       for symbol: Character in characters {
         print("utf8 (\(symbol.utf8)): ", terminator: "")
         symbol.utf8.forEach { byte in print("\(byte) ", terminator: "") }
         print("\nunicodes \(symbol.unicodeScalars)")
         for possibly₋canonic in symbol.unicodeScalars { /* ⬷ UInt32. */
           let possibly₋canonic₂ = 
  Int(truncatingIfNeeded: possibly₋canonic.value)
           switch possibly₋canonic₂ {
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

