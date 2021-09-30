/*  􀣳 terms.swift | histories logged. */

import AppKit
import ClibTwinbeam
import Metal /* ⬷ alt․ AppKit + Metal. */

class Rendition {
  
  var minimumview: Minimumview
  init(_ view: Minimumview) { self.minimumview = view }
  static let paper = NSColor(calibratedWhite: 0.95, alpha: 1.0), 
   crepe = NSColor(calibratedWhite: 0.05, alpha: 1.0), 
   paperborder = NSColor(calibratedWhite: 0.75, alpha: 1.0)
  static let cropmarks = NSColor(calibratedWhite: 0.70, alpha: 1.0)
  static let fine₋grid = NSColor(calibratedWhite: 0.92, alpha: 1.0), 
   coarse₋grid = NSColor(calibratedWhite: 0.88, alpha: 1.0)
  static let systemfont = NSFont.systemFont(ofSize: 30.0), 
   textfont = NSFont(name: "SF Mono", size: 9)
  static let zinkwhite = NSColor(calibratedWhite: 0.99, alpha: 1.0), 
   Ti₋white = NSColor(calibratedWhite: 0.90, alpha: 1.0), 
   textcolor = NSColor.labelColor, 
   textcolor₂ = NSColor.secondaryLabelColor, 
   ⁻¹textcolor = zinkwhite, ⁻¹textcolor₂ = Ti₋white
  static let frame₋anfang = NSRect(x: 120.0, y: 50.0, width: 48.0, height: 48.0)
  
  /* …for visible work and for non-visible work respectively ⤐ */
  let operations₁ = DispatchQueue(label: "myops", attributes: .concurrent)
  let operations₂ = DispatchQueue(label: "myjobs" /* , attributes: .serial */)
  /* ⬷ samgörande alt․ schemalaggda (▚). */
  
  struct theme { var ink: NSColor; var isDark: Bool }
  var themes = [ theme(ink: textcolor, isDark: false), theme(ink: ⁻¹textcolor, 
   isDark: true) ]
  var theme₋idx: Int = -1
  
  var original = ᴮʳTektron() /* ⬷ textual text may have been machine-read. (Not Array<CChar32>) */
  var linebreaks = Array<Int>() /* ⬷ a․𝘬․a lfAndEot₋deltas. */
  var patchwork = Quilt() /* ⬷ graphic text definitely machine-read. */
  
  var default₋textattrs: [NSAttributedString.Key: Any] {
    get {
      guard let font = Rendition.textfont else { return [:] }
      let ink = themes[theme₋idx].ink.cgColor
      return [.font: font, .foregroundColor: ink]
    }
  }
  
  struct layers { let text=CATextLayer() 
   var layers₋with₋illustrations = Dictionary<UUID,CALayer>()
   var rendered₋images = Dictionary<UUID,CGImage>()
   var layers₋with₋realtime = Dictionary<UUID,CAMetalLayer>()
   var scribbles = Dictionary<UUID,feedback>()
   class feedback { var explained=CAShapeLayer(); var symbols=CATextLayer() }
  }
  
  var assemble₋pieces = layers()
  let composition₋with₋scribbles = CALayer()
  
  var pointerIsOver: Bool = false /* ⬷ you should hit₋test this on init. */
  var hasPointerEntered: Bool = false /* ⬷ you should hit₋test this on init. */
  var y₋offset: CGFloat = 0.0 /* ⬷ visible rect, overdraw and underdraw. */
  var x₋offset: CGFloat = 0.0 /* ⬷ allows for horizontal scrolling including max line length in document. */
  func total₋twopass₋and₋height₋and₋width₋in₋O₍n₎() -> NSPoint { return 
   self.minimumview.convertFromBacking(NSMakePoint(100.0, 100.0)) }
  
  enum anchor { case middle; case ul; case ll; case ur; case lr }
  enum type₋of₋layer { case simulation₋interaction; case illustration }
  
  let post₋init₋layer = { (_ layer: inout CALayer) -> Void in 
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
  
  func add₋rendition₋layer(layer₋type: type₋of₋layer, name: String, 
   canvas₋initial: NSPoint, canvas₋size: NSSize, origo₋relative₋superlayer: 
   anchor) -> UUID {
    var sublayer: CALayer? = nil
    let ident = UUID()
    switch layer₋type {
    case .simulation₋interaction:
     let layer = CAMetalLayer()
     self.assemble₋pieces.layers₋with₋realtime.updateValue(layer, forKey: ident)
     sublayer = layer
    case .illustration: /* ₋and₋photography. */
     let layer = CALayer()
     self.assemble₋pieces.layers₋with₋illustrations.updateValue(layer, forKey: ident)
     sublayer = layer
    } /* ⬷ note 'doublesided' defaults to true. */
    if var addition = sublayer {
      addition.frame = CGRect(x: canvas₋initial.x, y: canvas₋initial.y, 
       width: canvas₋size.width, height: canvas₋size.height)
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
      composition₋with₋scribbles.addSublayer(addition)
      /* setNeedsLayout() setNeedsDisplay() setNeedsDisplayInRect(r: CGRect) */
    }
    return ident
  }
   
}

extension Rendition { /* ⬷ minimum and illustrations. */
   
  func render₋illustrations( 
    from₋wire ⁸textual: UnsafeBufferPointer<UnsafeMutablePointer<Tetra𝘖rUnicode>>, 
    topLeftNextGround: NSEdgeInsets, 
    typeset₋in columns: Int
   )
   {
   /*
     var parent₋cursor₋X=topLeftNextGround.left
     var parent₋cursor₋Y=topLeftNextGround.top
     let machine = Drawings₁(); var max₋height=0.0; var colno=1
     
     print("render \(columns) columns, inset \(topLeftNextGround) with \(⁸textual)")
     
     do { var size = CGSize(width: 0.0, height: 0.0); var name: String = "" 
       guard let address = ⁸textual.baseAddress else { return }
	   let layer = CALayer()
//       let layer: CALayer = try /* await */ machine.interpret(bytes: ⁸textual.count, 
//        figure₋utf8: address, nil, size: &size, name: &name)
       layer.frame = NSRect(x: parent₋cursor₋X, y: parent₋cursor₋Y, width: size.width, height: size.height)
       max₋height = max(layer.frame.height,max₋height)
       layer.name = name
       colno = (colno + 1) % columns
       if colno == 0 {
         parent₋cursor₋X = topLeftNextGround.left
         parent₋cursor₋Y += max₋height
         max₋height = 0.0
       }
       else {
         parent₋cursor₋X = size.width + topLeftNextGround.right
       }
       
       let ident = UUID()
       self.assemble₋pieces.layers₋with₋illustrations.updateValue(layer, forKey: ident)
       composition₋with₋scribbles.addSublayer(layer)
     } catch _ /* Drawings₁.Anomality.Rendition */ { print("render: exception") }
    /* for (idx,figure) in illusts.enumerated() { /* ⬷ a․𝘬․a figures. */ } */
    /* try figure.text.withUTF8 { fromwire₋utf8 /* UnsafeBufferPointer<UInt8> */ in 
      let utf8₋material = fromwire₋utf8.baseAddress! as? UnsafeMutablePointer<UInt8> } */
	   
	   */
   }
}

extension Rendition { /* ⬷ decoration */
  func apply₋ornaments() {
    self.letgo₋all₋ornaments()
    let rect = NSRect(x: 10, y: 10, width: 100, height: 100)
    let local₋cursor: NSCursor = NSCursor.dragCopy
    minimumview.addCursorRect(rect, cursor: local₋cursor)
    let strategy₁ = {
      let userdata: UnsafeMutableRawPointer? = nil
      let _ /* tag */: NSView.TrackingRectTag = self.minimumview.addTrackingRect(rect, owner: self, 
       userData: userdata, assumeInside: true)
       self.minimumview.updateTrackingAreas()
    }
 /* let _ /* strategy₂ */ = { tracking₋bounds: NSRect in 
      let opts: NSTrackingArea.Options = [.cursorUpdate, .mouseEnteredAndExited, .activeInKeyWindow]
      /* let opts = [NSTrackingArea.Options.activeAlways, NSTrackingArea.Options.mouseMoved, NSTrackingArea.Options.mouseEnteredAndExited] */
      let area = NSTrackingArea(rect: tracking₋bounds, options: opts, owner: self, userInfo: nil)
      self.addTrackingArea(area)
    } */
    strategy₁()
  }
  func letgo₋all₋ornaments() { for area in minimumview.trackingAreas { minimumview.removeTrackingArea(area) } }
}

extension Rendition { /* ⬷ interaction */
  func hit₋test(point: CGPoint) -> CALayer? { return composition₋with₋scribbles.hitTest(point) }
}

extension Rendition {
  func washline() {
    operations₂.async { DispatchQueue.main.async {
    } }
  }
  func definition() {
    operations₂.async { DispatchQueue.main.async {
      let attribed = NSAttributedString(string: "Hello world")
      let baseline₋origin = NSPoint()
      self.minimumview.showDefinition(for: attribed, at: baseline₋origin)
      let target₋range = NSRange()
      let options = [NSView.DefinitionOptionKey:Any]()
      let baselineOriginProvider = { (adjustedRange: NSRange) -> NSPoint in return NSPoint(x: 0, y: 0) }
      self.minimumview.showDefinition(for: attribed, range: target₋range, options: options, 
        baselineOriginProvider: baselineOriginProvider)
    } }
  } /* ⬷ popover level 2 (åkerplättransgressionell). */
  func start₋find₋in₋forks() {
    operations₂.async { DispatchQueue.main.async {
      /* minimumview.drawingFindIndicator = true */
      /* NotificationCenter.send() */
    } }
  }
  func turn₋off₋character₋attributes() { } /* ⬷ ^[[m and ^[[0m. */
  func turn₋bold₋mode₋on() { } /* ⬷ ^[[1m. */
  func turn₋low₋intensity₋mode₋on() { } /* ⬷ ^[[2m. */
  func turn₋underline₋mode₋on() { } /* ⬷ ^[[4m. */
  func turn₋reverse₋video₋on() { } /* ⬷ ^[[7m. */
  func turn₋invisible₋text₋mode₋on() { } /* ⬷ [[8m. */
  func erase₋to₋end₋of₋current₋line() { } /* ⬷ a․𝘬․a kill₋other₋on₋line and ^K. */
  func move₋cursor₋left₋one₋char() { } /* ⬷ ^[D and ^[C and ^[H and ^[A and ^[B. */
  func cursorpos(v: Int, h: Int) { } /* ⬷ ^[<v><h>. */
  func kill₋entire₋line() { } /* ⬷ ^U. */
  func delete₋erase₋symbol() { } /* ⬷ ^H and 'delete' and 0x08. */
  func suspend₋process() { } /* ^Z. */
  func kill₋process() { } /* ⬷ ^U. */
  func foreground₋process() { } /* ⬷ 'prompt> fg'. */
  func send₋eof() { } /* ⬷ ^D. */
  func pause₋scroll() {
    operations₂.async { DispatchQueue.main.async {
    } }
  } /* ⬷ ^S. */
  func scroll₋down₋one₋line() { } /* ⬷ ^[M. */
  func scroll₋up₋one₋line() { } /* ⬷ ^[D. */
  func unpause₋scroll() {
    operations₂.async { DispatchQueue.main.async {
    } }
  } /* ⬷ ^Q. */
  func toggle₋pause₋auto₋scroll(enabled: Bool) {
    operations₂.async { DispatchQueue.main.async {
    } }
  }
}

typealias Reference = UnsafeMutablePointer /* ⬷ a C language pointer: both access and manipulation. */
typealias Nonownings = UnsafeMutableBufferPointer<Tetra𝘖rUnicode> /* ⬷ no manipulations of characters. */
typealias Voidstar = UnsafeMutableRawPointer /* ⬷ crossing at least two language barriers. */

class Minimumview: NSView {
  
  init(frame frameRect: NSRect, controller ctrl: Viewcontroller) {
    print("minimumview-init")
    self.controller = ctrl /* ⬷ must be before hierachial init. */
    super.init(frame: frameRect)
    self.layerContentsRedrawPolicy = NSView.LayerContentsRedrawPolicy.onSetNeedsDisplay
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
  
  override var isOpaque: Bool { false }
  
  override func setFrameSize(_ newSize: NSSize) {
    print("setFrameSize")
    super.setFrameSize(newSize)
  }
  
  var controller: Viewcontroller
  
}

func Type₋continuing₋character(_ uc: UInt32) -> Bool
{
   return (0x300 <= uc && uc <= 0x360) || /* ⬷ combining diacritical marks. */
    (0x1AB0 <= uc && uc <= 0x1AFF) || /* ⬷ combining diacritical marks extended. */
    (0x1DC0 <= uc && uc <= 0x1DFF) || /* ⬷ combining diacritical marks supplement. */
    (0x20D0 <= uc && uc <= 0x20FF) || /* ⬷ combining diacritical marks for symbols. */
    (0xFE20 <= uc && uc <= 0xFE2F) /* ⬷ combining half marks. */
} /* ⬷ documented to be 'identic to the Mc Unicode Character 
 Property' consisting of 445 characters and not equal to the U+1F16A Unicode. In 
 Swift named 'extended grapheme cluster' a․𝘬․a Character 𝘦․𝘨 \u{E9}\u{20DD} and in 
 UAX # 29 legacy/extended is base followed by zero or more continuing characters. 
 A basic unit may consist of multiple Unicode code points. */

func Type₋private₋use(_ uc: UInt32) -> Bool
{
   return (0xE000 <= uc && uc <= 0xF8FF) || 
    (0xF0000 <= uc && uc <= 0xFFFFD) || 
    (0x100000 <= uc && uc <= 0x10FFFD)
}

func Append₋opt₋allocate() -> Reference<UInt32>
{
   let pointer = Reference<UInt32>.allocate(capacity: 5)
   pointer[0] = 0x0041
   pointer[1] = 0x0042
   pointer[2] = 0x0043
   pointer[3] = 0x0044
   pointer[4] = 0x1f610
   return pointer
}

extension Minimumview {
  func attribute₋text₋in₋window(count: Int, 
   material: Reference<UInt32>) -> NSAttributedString {
    let raw = UnsafeMutableRawPointer(material)
    let invariant = String(bytesNoCopy: raw, length: 4*count, encoding: 
     .utf32LittleEndian, freeWhenDone: false)
    let attributed = NSAttributedString(string: invariant!, attributes: 
     controller.rendition.default₋textattrs)
    return attributed
  }
  func typeset₋83(_ attributed: NSAttributedString, 
   context: CGContext) -> Void {
    let framesetter = CTFramesetterCreateWithAttributedString(attributed)
    let symbols = CFRangeMake(0,attributed.length)
    let box = self.bounds.insetBy(dx: 16, dy: 16).offsetBy(dx: 16, dy: -16)
    let path = CGPath(rect: box.insetBy(dx: 8, dy: 8), transform: nil)
    let textFrame = CTFramesetterCreateFrame(framesetter,symbols,path,nil)
    CTFrameDraw(textFrame,context)
  }
  func snapshot₋rendition() -> NSBitmapImageRep? {
    let rectangle = controller.rendition.assemble₋pieces.text.frame 
    let bitmap: NSBitmapImageRep? = self.bitmapImageRepForCachingDisplay(in: rectangle)
    return bitmap
  } /* bitmap.planar, bitmap.samplesPerPixels, ... */
  override func draw(_ dirty: CGRect) {
    print("draw-rect: \(dirty) self.frame now is \(self.frame)")
    guard let context = NSGraphicsContext.current?.cgContext else { return }
    let pointer = Append₋opt₋allocate()
    let attributed = attribute₋text₋in₋window(count: 5, material: pointer)
    typeset₋83(attributed, context: context)
    super.draw(dirty)
  }
}

/* extension Minimumview {
  func loupe₋overlayed(_ sender: AnyObject) {
    /* let bounds = CGContextConvertRectToDeviceSpace() */
    /* composition.minificationFilter = CALayer.trilinear 
    composition.magnificationFilter = CALayer.trilinear */
    /* CALayerContentsFilter */
  } /* ⬷ protocol-􀤎. */
  enum Perspective { case undo; case redo; case hidden₋detailed }
  func perspective₋toggled(_ sender: AnyObject) { } /* ⬷ 􀢅􀢇􀌆􀒱􀎮􀆔􀊅􀟪􀋘􀱀􀙟􀘽􀆃=􀃌. */
} */

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
    /* visualeffect.maskImage = NSImage(data: Data(contentsOf: url)) /​* ⬷ '130px-Cross-Pattee-Heraldry.png'. */
    self.view = visualeffect
    let material = Minimumview(frame: frame, controller: self)
    /* material.acceptsTouchEvents = true */
    material.allowedTouchTypes = [.indirect] /* ⬷ ipad = .direct */
    self.view.addSubview(material)
    let views = ["material" : minimumview]
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
    /* update the view if already loaded. */ }
  }
  
  var minimumview: Minimumview { get { self.view.subviews[0] as! Minimumview } }
  
  override var acceptsFirstResponder: Bool { true }
  
  override func cursorUpdate(with event: NSEvent) { print("cursorUpdate") 
    /* NSCursor.arrowCursor.set */
    /* NSCursor.dragCopyCursor.set */
    /* NSCursor.pointingHand.set */
    super.cursorUpdate(with: event)
  }
  
  func key(_ oval: NSTouch) -> String { return "\(oval.identity)" }
  
  var beginning₋touches = Dictionary<String,NSPoint>()
  var moved₋touches = Dictionary<String,NSPoint>()
  
  override func touchesBegan(with event: NSEvent) {
    /* let instant: TimeInterval = event.timestamp */
    let ovals: Set<NSTouch> = event.touches(matching: .began, in: view)
    for oval in ovals {
      let identity = key(oval)
      beginning₋touches[identity] = oval.normalizedPosition
    }
  }
  
  override func touchesMoved(with event: NSEvent) {
    /* let instant: TimeInterval = event.timestamp */
    let ovals: Set<NSTouch> = event.touches(matching: .moved, in: view)
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
    }
  }
  
  override func touchesEnded(with event: NSEvent) {
    /* let instant: TimeInterval = event.timestamp */
    let ovals: Set<NSTouch> = event.touches(matching: .ended, in: view)
    for oval in ovals {
      let identity = key(oval)
      beginning₋touches.removeValue(forKey: identity)
      moved₋touches.removeValue(forKey: identity)
    }
  }
  
  override func pressureChange(with event: NSEvent) {
    /* let instant: TimeInterval = event.timestamp */
    let pressure = event.pressure
    print("pressureChange \(pressure)")
  }
  
  override func scrollWheel(with event: NSEvent) { }
  
  override func touchesCancelled(with event: NSEvent) { print("touchesCancelled") }
  
  @objc func addScribblelayer(_ sender: AnyObject) { print("Adding scribbleview") }
  
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
  
} /* ⬷ also keyed 'run-block' and 'load-block'. In terminal implicit 'run-block'. */

extension Viewcontroller { /* ⬷ the menu */ 
  @objc func validateMenuItem(_ menuItem: NSMenuItem) -> Bool {
    print("validate menu for view")
    Viewcontroller.incorporate₋scribble₋in₋menu(include: true)
    guard let window = self.minimumview.window else { return false }
    return window.validateMenuItem(menuItem)
  }
}

class Windowcontroller: NSWindowController {
   
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
   
   /* CAAction: func run(forKey event: String, object anObject: Any, 
    arguments dict: [AnyHashable : Any]?) { } */
   
   let viewctrl = Viewcontroller()
   var shell = Interact()
   var recorder = UndoManager() /* ⬷ duplicate undo-manager incorrectly 
    placed inside NSResponder named 'undoManager'. */
   
   var minimumwindow: Minimumwindow { self.window as! Minimumwindow }
   var minimumview: Minimumview { minimumwindow.controller.minimumview }
   var rendition: Rendition { self.contentViewController!.representedObject as! Rendition }
   
   var graphics₋not₋text = false
   let separator = UInt32(0x0000008a)
   let Return = UInt32(0x0000000a)
   
   var read₋graphics: (@convention(c) (UInt32) -> Void)?
   
   func tektron(_ unicode: UInt32) {
     rendition.original.append(unicode) /* ⬷ Tx'ed from child. */
     if unicode == separator {
       if self.graphics₋not₋text { rendition.patchwork.graphics₋ended() }
       else { rendition.patchwork.graphics₋begin() }
       self.graphics₋not₋text = !self.graphics₋not₋text
     } else if graphics₋not₋text { read₋graphics!(unicode) }
   } /* ⬷ 1) Unicode code point == 32-bit word and 
      2) grapheme == smallest functional unit in a writing system and 
      3) grapheme cluster == multiple code points == a user-percieved-character. */
   
   @available(macOS 12.0.0, *)
   func corout₋textual₋and₋graphical₋output() async {
     let maxfour = Reference<UInt8>.allocate(capacity: 4)
     while true {
       guard let oldest = self.o₋material.first else { await Task.yield(); continue }
       var idx=0, errors=0; var unicode = Return
       while idx < oldest.count {
         let leadOr8Bit: UInt8 = oldest[idx]
         let followers₋and₋lead = (~leadOr8Bit).leadingZeroBitCount
         let followers = followers₋and₋lead - 1
         if followers >= 1 { maxfour[0] = leadOr8Bit 
           if idx + 1 < oldest.count { maxfour[1] = oldest[idx+1] } else { if o₋material.count == 1 { await Task.yield() } else { } }
           if idx + 2 < oldest.count { maxfour[2] = oldest[idx+2] } else { if o₋material.count == 1 { await Task.yield() } else { } }
           if idx + 3 < oldest.count { maxfour[3] = oldest[idx+3] } else { if o₋material.count == 1 { await Task.yield() } else { } }
         }
         if leadOr8Bit >= 128 {
           if 128 <= leadOr8Bit && leadOr8Bit < 192 { errors += 1; idx += followers₋and₋lead; continue; }
           if 248 <= leadOr8Bit { errors += 1; idx += followers₋and₋lead; continue }
           unicode = Utf8ToUnicode(ξ: maxfour, bytes: followers₋and₋lead)
         } else {
           unicode = UInt32(leadOr8Bit)
         }
         tektron(unicode)
         idx += followers₋and₋lead
       }
       self.o₋material.removeFirst()
       await Task.yield()
     }
   } /* ⬷ a․𝘬․a 'a coroutine that may suspend at any time'. 
    'löper samtidigt' ≢ async.
     let t₁ = Task.detached { }
     let t₂ = Task { await shell.slow-write... }
     t.cancel() */
   
   var o₋material = Array<Data>() /* ⬷ blocks of utf8 bytes not necessarily cut in full unicodes. */
   var i₋material = Array<String>() /* ⬷ possibly pasted strings of unicodes with ornaments. */
   
   override func windowDidLoad() { print("windowDidLoad") 
     self.viewctrl.representedObject = Rendition(self.minimumview)
     let AppleInterfaceThemeChangedNotification = NSNotification.Name(rawValue: "AppleInterfaceThemeChangedNotification")
     DistributedNotificationCenter.default.addObserver(self, 
      selector: #selector(reloadUi(sender:)),
      name: AppleInterfaceThemeChangedNotification,
      object: nil)
     shell.output = { (material: Data) in 
       self.o₋material.append(material)
       if #available (macOS 12.0.0, *) {
         Task { await self.corout₋textual₋and₋graphical₋output() }
       }
       if let str = String(data: material, encoding: .utf8) {
         print(str, terminator: "")
       }
     }
     shell.commence(execute: "zsh", parameters: [], path₋exe: "/bin/")
     reloadUi(sender: NSNotification(name: AppleInterfaceThemeChangedNotification, object: nil))
   }
   
   func windowWillReturnUndoManager(_ window: NSWindow) -> UndoManager? { return recorder }
   
   @objc func reloadUi(sender: NSNotification) { print("reloadUi") 
     guard let window = self.window else { return }
     if NSApp.effectiveAppearance.name != .aqua {
       /* window.appearance = NSAppearance(named: .darkAqua) */
       rendition.theme₋idx = 1
     } else {
       /* window.appearance = NSAppearance(named: .aqua) */
       rendition.theme₋idx = 0
     }
   }
   
   func validateMenuItem(_ menuItem: NSMenuItem) -> Bool {
     print("validate-window-menu")
     return NSApplication.shared.validateMenuItem(menuItem)
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
   
   var controller: Viewcontroller { get { self.contentViewController! as! Viewcontroller } }
   
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
   
}

extension Windowcontroller { /* ⬷ keyboard */
   
   func keyput(_ unicode: CChar32) {
     let text = String(unicode)
     shell.slow₋write₋to₋child(text)
   }
   
   override func keyDown(with event: NSEvent) {
     let spacekey = Unicode.Scalar(0x0020)
     if let characters = event.characters {
       for symbol: Character in characters {
         print("utf8 (\(symbol.utf8)): ", terminator: "")
         symbol.utf8.forEach { byte in print("\(byte) ", terminator: "") }
         print("\nkeydown unicodes \(symbol.unicodeScalars)")
         for possibly₋canonic in symbol.unicodeScalars { /* ⬷ the possibly₋canonic typed UInt32 later 'struct Unicode.Scalar' in Swift. */
           if possibly₋canonic == spacekey && minimumwindow.ctrl { rendition.washline() }
           else { keyput(possibly₋canonic) }
         }
       }
     }
   }
  
   override func noResponder(for event: Selector) { print("no responder for \(event)") }
  
}

