/*  􀣳 terms.swift | histories logged. */

import AppKit
import ClibTwinbeam
import Metal /* ⬷ alt․ AppKit + Metal. */

class Rendition {
   var original = Array<UInt32>() /* ⬷ textual text may have been machine-read. */
   var linebreaks = Array<Int>() /* ⬷ a․𝘬․a lf₋locations. */
   typealias Graphicstext = UnsafeMutableBufferPointer<UInt32>
   var graphics = Array<Graphicstext>()
   
   static let paper = NSColor(calibratedWhite: 0.95, alpha: 1.0), 
    crepe = NSColor(calibratedWhite: 0.05, alpha: 1.0), 
    paperborder = NSColor(calibratedWhite: 0.75, alpha: 1.0)
   static let cropmarks = NSColor(calibratedWhite: 0.70, alpha: 1.0)
   static let fine₋grid = NSColor(calibratedWhite: 0.92, alpha: 1.0), 
    coarse₋grid = NSColor(calibratedWhite: 0.88, alpha: 1.0)
   static let systemfont = NSFont.systemFont(ofSize: 30.0), 
    textfont = NSFont(name: "SF Mono", size: 9)!
   static let zinkwhite = NSColor(calibratedWhite: 0.99, alpha: 1.0), 
    Ti₋white = NSColor(calibratedWhite: 0.90, alpha: 1.0), 
    textcolor = NSColor.labelColor, 
    textcolor₂ = NSColor.secondaryLabelColor, 
    ⁻¹textcolor = zinkwhite, ⁻¹textcolor₂ = Ti₋white
   static let frame₋anfang = NSRect(x: 120.0, y: 50.0, width: 48.0, height: 48.0)
   
   var theme₋idx: Int = -1; struct theme { var ink: NSColor; var isDark: Bool }
   var themes = [ theme(ink: textcolor, isDark: false), theme(ink: ⁻¹textcolor, 
    isDark: true) ]
   
   var default₋textattrs: [NSAttributedString.Key: Any] {
     get {
       let ink = themes[theme₋idx].ink.cgColor
       return [.font: Rendition.textfont, .foregroundColor: ink]
     }
   }
   
   /* …for visible work and for non-visible work respectively ⤐ */
   let operations₁ = DispatchQueue(label: "myops", attributes: .concurrent)
   let operations₂ = DispatchQueue(label: "myjobs" /* , attributes: .serial */)
   /* ⬷ samgörande alt․ schemalaggda (▚). */
   
   struct layers {
    var illustrations = Array<Artworklayer>()
    var layers₋with₋realtime = Array<Simulationlayer>()
    var still₋images = Array<CGImage>()
    /* var scribbles = Dictionary<UUID,feedback>()
    class feedback { var explained=CAShapeLayer(); var symbols=CATextLayer() } */
   }
   
   var assemble₋pieces = layers()
   let composition₋with₋scribbles = CALayer()
   
   var pointerIsOver: Bool = false /* ⬷ you should hit₋test this on init. */
   var hasPointerEntered: Bool = false /* ⬷ you should hit₋test this on init. */
   var y₋offset: CGFloat = 0.0 /* ⬷ visible rect, overdraw and underdraw. */
   var x₋offset: CGFloat = 0.0 /* ⬷ allows for horizontal scrolling including max line length in document. */
   
   enum anchor { case middle; case ul; case ll; case ur; case lr }
   enum type₋of₋layer { case simulation₋interaction; case illustration }
   
   /* let post₋init₋layer = { (_ layer: inout CALayer) -> Void in 
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
      self.assemble₋pieces.illustrations.updateValue(layer, forKey: ident)
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
     }
     return ident
   } */
   
   func attribute₋text₋in₋window(count: Int, 
    material: Reference<UInt32>) -> NSAttributedString {
     let raw = UnsafeMutableRawPointer(material)
     let invariant = String(bytesNoCopy: raw, length: 4*count, encoding: 
      .utf32LittleEndian, freeWhenDone: false)
     let attributed = NSAttributedString(string: invariant!, attributes: 
      default₋textattrs)
     return attributed
   }
   func typeset(_ attributed: NSAttributedString, frame: NSRect, context: CGContext) -> Void {
     let framesetter = CTFramesetterCreateWithAttributedString(attributed)
     let symbols = CFRangeMake(0,attributed.length)
     let box = frame.insetBy(dx: 2, dy: 2).offsetBy(dx: 1, dy: 1)
     let path = CGPath(rect: box.insetBy(dx: 1, dy: 1), transform: nil)
     let textframe = CTFramesetterCreateFrame(framesetter,symbols,path,nil)
     CTFrameDraw(textframe,context)
   }
   func interpret(count: Int, textual: Reference<UInt32>, height: inout CGFloat) throws -> Artworklayer {
     var artwork₁ = Artwork₋swift(text: ".width-and-height 50.0, 50.0 ")
     var artwork₂ = Artwork₋swift(text: 
"""
.pixel-height 100.0
start-line 50.0 50.0 last-line 75.0 75.0
next
.pixel-height 100.0
start-line 10.0 10.0 last-line 20.0 20.0
""")
     var artwork = artwork₂
     var s₋ctxt = Scanner₋ctxt()
     let unicodes = UnsafeMutablePointer<UInt32>(mutating: textual)
     let y = Parse₋Artwork₋LL₍1₎(Int64(count),unicodes,&s₋ctxt,Append₋instruction)
     let layer = Artworklayer()
     layer.contents = artwork
     guard let directive: Artwork₋directive = artwork.directives[pixel₋height] else { return layer }
     let height: Double = directive.Scalar
     /* let height: Double = To₋doubleprecision(height) */
     layer.bounds = CGRect(x: 0, y: 0, width: 400.0, height: height)
     layer.anchorPoint = CGPoint(x: 0.0, y: 0.0)
     layer.position = CGPoint()
     return layer
   }
   func illustrations(unicodes text: Graphicstext, height: inout CGFloat) {
     let layer = Artworklayer(); let ident = UUID()
     let width = Rendition.textfont.boundingRectForFont.width * 83
     var size=CGSize(width: width, height: 0.0)
     do {
       let layer: Artworklayer = try interpret(count: text.count, textual: 
        text.baseAddress!, height: &size.height)
     } catch _ { print("render exception") }
     /* self.assemble₋pieces.illustrations.updateValue(layer, forKey: ident) */
     self.assemble₋pieces.illustrations.append(layer)
      
  /*  var parent₋cursor₋X=topLeftNextGround.left
      var parent₋cursor₋Y=topLeftNextGround.top
      let machine = Drawings₁(); var max₋height=0.0; var colno=1
      
      print("render \(columns) columns, inset \(topLeftNextGround) with \(⁸textual)")
      
      do { var size = CGSize(width: 0.0, height: 0.0); var name: String = "" 
        guard let address = ⁸textual.baseAddress else { return }
      /* let layer: CALayer = try /* await */ machine.interpret(bytes: ⁸textual.count, 
         figure₋utf8: address, nil, size: &size, name: &name) */
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
        controller.rendition.composition₋with₋scribbles.addSublayer(layer)
      } catch _ /* Drawings₁.Anomality.Rendition */ { print("render: exception") }
       */
   }
   
   var unicode₋count = 0
   var text₋is₋graphics = false
   var start₋graphics = 0
   
   func tektron(_ unicode: UInt32) {
     self.original.append(unicode)
     if unicode == 0x0a { self.linebreaks.append(unicode₋count) }
     if unicode == 0x8a { text₋is₋graphics = !text₋is₋graphics
       if text₋is₋graphics { start₋graphics = unicode₋count }
       else { /* graphics ended ⤐ */
         let symbols = unicode₋count - start₋graphics
         let pointer = Reference<UInt32>.allocate(capacity: symbols)
         let text = Graphicstext(start: pointer, count: symbols)
         for i in 0..<symbols {
           text[i] = self.original[start₋graphics+i]
         }
         self.graphics.append(text)
       }
     }
     unicode₋count += 1
   }
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
 UAX #29 legacy/extended is base followed by zero or more continuing characters. 
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
      self.setNeedsDisplay(frame₋update)
    }
    /* init₋for₋dropping(NSFilenamesPboardType) */
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
    print("setFrameSize")
    super.setFrameSize(newSize)
  }
  
}

extension Minimumview { /* ⬷ text drawing. */
  
  var total₋twopass₋and₋height₋and₋width₋in₋O₍n₎: NSPoint {
    get {
      let linecount = CGFloat(controller.rendition.linebreaks.count); let vspace=5.0
      let textfont = Rendition.textfont
      let lineheight = textfont.xHeight + textfont.ascender + textfont.descender
      let height: CGFloat = linecount*lineheight + (linecount - 1)*vspace + 2
      let everyfit = textfont.boundingRectForFont
      let width₋visible = 2 + everyfit.size.width*83 + (82*2)
      return self.convertFromBacking(NSMakePoint(width₋visible,height))
    }
  }
  func textlines(onebased number: Int, first: inout Nonabsolute, 
   last: inout Nonabsolute) {
    let start = number - 1, end=number
    if start < 0 { first=0 } else {
      first = Nonabsolute(controller.rendition.linebreaks[start])
    }
    last = Nonabsolute(controller.rendition.linebreaks[end])
  }
  func visibles(offset: CGFloat, tiles: inout Array<UInt32>) {
  }
  override func draw(_ dirty: CGRect) {
    print("draw-rect: \(dirty) self.frame now is \(self.frame)")
    guard let context = NSGraphicsContext.current?.cgContext else { return }
    var tiles = Array<Reference<UInt32>>()
    visibles(offset: controller.rendition.y₋offset, tiles: &controller.rendition.original)
    let pointer = Append₋opt₋allocate()
    let attributed = controller.rendition.attribute₋text₋in₋window(count: 5, material: pointer)
    controller.rendition.typeset(attributed, frame: self.frame, context: context)
    super.draw(dirty)
  }
  func snapshot₋rendition() -> NSBitmapImageRep? {
    /* let uuid = UUID() */
    let rectangle = controller.rendition.assemble₋pieces.illustrations[0].frame
    let bitmap: NSBitmapImageRep? = self.bitmapImageRepForCachingDisplay(in: rectangle)
    return bitmap
  }
}

extension Minimumview { /* ⬷ decoration. */
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
 /* let _ /* strategy₂ */ = { tracking₋bounds: NSRect in 
      let opts: NSTrackingArea.Options = [.cursorUpdate, .mouseEnteredAndExited, .activeInKeyWindow]
      /* let opts = [NSTrackingArea.Options.activeAlways, NSTrackingArea.Options.mouseMoved, NSTrackingArea.Options.mouseEnteredAndExited] */
      let area = NSTrackingArea(rect: tracking₋bounds, options: opts, owner: self, userInfo: nil)
      self.addTrackingArea(area)
    } */
    strategy₁()
  }
  func letgo₋all₋ornaments() { for area in self.trackingAreas { self.removeTrackingArea(area) } }
}

extension Rendition { /* ⬷ interaction. */
  func hit₋test(point: CGPoint) -> CALayer? { return composition₋with₋scribbles.hitTest(point) }
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
  /* Prefix-suffix .swift alt. object-ive-se. */
  /* Shanghainese mutually unintelligible with 𝘦․𝘨 Mandarin. */
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
    let material = Minimumview(frame: frame)
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
     minimumview.setNeedsDisplay(minimumview.frame) }
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
      /* top to botton prints magnitude from 0 to approximately -0.97. */
      let rect: CGRect = minimumview.frame
      let physical₋size = ovals[𝟶].deviceSize
      minimumview.setNeedsDisplay(rect)
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

extension Viewcontroller {
  func washline() {
    rendition.operations₂.async { DispatchQueue.main.async {
    } }
  }
  func definition() {
    rendition.operations₂.async { DispatchQueue.main.async {
      let attribed = NSAttributedString(string: "Hello world")
      let baseline₋origin = NSPoint()
      /* self.minimumview.showDefinition(for: attribed, at: baseline₋origin)
      let target₋range = NSRange()
      let options = [NSView.DefinitionOptionKey:Any]()
      let baselineOriginProvider = { (adjustedRange: NSRange) -> NSPoint in return NSPoint(x: 0, y: 0) }
      self.minimumview.showDefinition(for: attribed, range: target₋range, options: options, 
        baselineOriginProvider: baselineOriginProvider) */
    } }
  }
  func start₋find₋in₋forks() {
    rendition.operations₂.async { DispatchQueue.main.async {
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
    rendition.operations₂.async { DispatchQueue.main.async {
    } }
  } /* ⬷ ^S. */
  func scroll₋down₋one₋line() { } /* ⬷ ^[M. */
  func scroll₋up₋one₋line() { } /* ⬷ ^[D. */
  func unpause₋scroll() {
    rendition.operations₂.async { DispatchQueue.main.async {
    } }
  } /* ⬷ ^Q. */
  func toggle₋pause₋auto₋scroll(enabled: Bool) {
    rendition.operations₂.async { DispatchQueue.main.async {
    } }
  }
}

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
     self.init(window: nil) }
   override init(window: NSWindow?) { print("windowcontroller-window-init") 
     super.init(window: window) }
   
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
   
   let viewctrl = Viewcontroller()
   var shell = Interact()
   var recorder = UndoManager() /* ⬷ duplicate undo-manager incorrectly 
    placed inside NSResponder named 'undoManager'. */
   
   var minimumwindow: Minimumwindow { self.window as! Minimumwindow }
   var minimumview: Minimumview { viewctrl.view as! Minimumview }
   var rendition: Rendition { viewctrl.representedObject as! Rendition }
   
   @available(macOS 12.0.0, *)
   func corout₋textual₋and₋graphical₋output() async {
     let maxfour = Reference<UInt8>.allocate(capacity: 4)
     while true {
       guard let oldest = self.o₋material.first else { await Task.yield(); continue }
       var idx=0, errors=0; var unicode = UInt32(0)
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
         rendition.tektron(unicode)
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
   var i₋material = Array<UInt32>() /* ⬷ possibly pasted strings of unicodes with ornaments. */
   
   override func windowDidLoad() { print("windowDidLoad") 
     self.viewctrl.representedObject = Rendition()
     shell.output = { (material: Data) in 
       self.o₋material.append(material)
       if #available (macOS 12.0.0, *) {
         Task { await self.corout₋textual₋and₋graphical₋output() }
       } else {
         if let unicodes = String(data: material, encoding: .utf8) {
           unicodes.forEach { (symbol: Character) -> Void in 
             for possibly₋canonic in symbol.unicodeScalars {
               let uc = possibly₋canonic.value
               self.rendition.tektron(uc)
               let s = String(format: "%02x ", uc); print("storing \(s)")
             }
           }
         }
       }
       let rect = self.minimumview.frame
       self.minimumview.setNeedsDisplay(rect) /* alt. DispatchQueue.main.async { ... } */
     }
     shell.commence(execute: "zsh", parameters: [], path₋exe: "/bin/")
     let AppleInterfaceThemeChangedNotification = 
      NSNotification.Name(rawValue: "AppleInterfaceThemeChangedNotification")
     reloadUi(sender: NSNotification(name: AppleInterfaceThemeChangedNotification, object: nil))
     DistributedNotificationCenter.default.addObserver(self, 
      selector: #selector(reloadUi(sender:)),
      name: AppleInterfaceThemeChangedNotification,
      object: nil)
   }
   
   func windowWillReturnUndoManager(_ window: NSWindow) -> UndoManager? { return recorder }
   
   @objc func reloadUi(sender: NSNotification) { print("reloadUi") 
     if NSApp.effectiveAppearance.name != .aqua 
     { rendition.theme₋idx = 1 } else { rendition.theme₋idx = 0 }
   }
   
   func validateMenuItem(_ menuItem: NSMenuItem) -> Bool {
     print("validate-window-menu")
     return NSApplication.shared.validateMenuItem(menuItem)
   }
}

extension Windowcontroller { /* ⬷ for keyboard. */
   func keyput(_ unicode: UInt32) { 
     shell.slow₋write₋to₋child(unicode)
     i₋material.append(unicode) }
   override func keyDown(with event: NSEvent) {
     let spacekey = Unicode.Scalar(0x20)
     if let characters = event.characters {
       for symbol: Character in characters {
         for possibly₋canonic in symbol.unicodeScalars {
           if possibly₋canonic == spacekey && minimumwindow.ctrl { viewctrl.washline() }
           else { var uc: UInt32 = possibly₋canonic.value
             if uc == 0xd { uc = 0xa }
             keyput(uc)
           }
         }
       }
     }
   }
}

class Artwork₋swift {
  init(text: String) { self.text = text 
   let default₋pixel₋height = 100.0
   let default₋pixel₋origo = A₋point(x: 50.0, y: 50.0)
   let default₋offset₋drawing₋on = A₋size(x: 0.0, y: 0.0)
   directives[pixel₋height] = Artwork₋directive(Scalar: default₋pixel₋height)
   directives[place₋origo] = Artwork₋directive(Point: default₋pixel₋origo)
   directives[offset₋drawing₋on] = Artwork₋directive(Size: default₋offset₋drawing₋on) }
  convenience init() { self.init(text: "") }
  var directives = Dictionary<Artwork₋instruction,Artwork₋directive>()
  typealias Artwork₋parameters = (Double,Double,Double,Double,Double,Double)
  struct operation { var instruction: Artwork₋instruction 
   var params: Artwork₋parameters; var texts: (String,String)? }
  var instructions = Array<operation>()
  var size = CGSize(width: 100, height: 100)
  var text: String
}

func Append₋instruction(_ instruction: Int32, detail: 
 Artwork₋instruction₋detail, ctx: UnsafeMutableRawPointer?)
{
   let recorder = ctx!.load(as: Artwork₋swift.self)
   let instr = Artwork₋instruction(rawValue: UInt32(instruction))
   /* let cpointer: UnsafeMutablePointer<CDouble> = detail.four₋parameters!
   let rawpointer = UnsafeMutableRawPointer(cpointer)
   let ⁴doubles: UnsafeMutablePointer<CDouble> = rawpointer.bindMemory(to: 
    CDouble.self, capacity: 4) */
   let ⁴doubles = UnsafeBufferPointer(start: detail.four₋parameters, count: 4)
   if instr == pixel₋height {
     recorder.directives[instr] = Artwork₋directive(Scalar: ⁴doubles[0])
   } else if instr == place₋origo {
     recorder.directives[instr] = Artwork₋directive(Point: A₋point(x: ⁴doubles[0], y: ⁴doubles[1]))
   } else if instr == offset₋drawing₋on {
     recorder.directives[instr] = Artwork₋directive(Size: A₋size(x: ⁴doubles[0], y: ⁴doubles[1]))
   } else {
     let params: Artwork₋swift.Artwork₋parameters = (⁴doubles[0],⁴doubles[1], 
      ⁴doubles[2],⁴doubles[3],⁴doubles[4],⁴doubles[5])
     let op = Artwork₋swift.operation(instruction: instr, params: params, texts: nil)
     recorder.instructions.append(op)
   }
}

extension Artwork₋instruction: Hashable {
  public func hash(into hasher: inout Hasher) { hasher.combine(self.rawValue) }
  static func == (lhs: Artwork₋instruction, rhs: Artwork₋instruction) -> Bool { return lhs.rawValue == rhs.rawValue }
}

class Artworklayer: CALayer {
  enum Anomality: Error { case Image }
  override func draw(in omgivning: CGContext) {
    let figure: Artwork₋swift = self.contents as! Artwork₋swift
    for op in figure.instructions {
      let params = op.params
      switch op.instruction {
       case beziercurve₋initial:
         omgivning.beginPath()
         let x=op.params.0, y=op.params.1
         omgivning.move(to: CGPoint(x: x, y: y))
       case beziercurve₋add:
         var x1=params.0,y1=params.1,x2=params.2,y2=params.3,x3=params.4,y3=params.5
         omgivning.addCurve(to: CGPoint(x: x1, y: y1), control1: CGPoint(x: x2, y: y2), control2: CGPoint(x: x3, y: y3))
       case beziercurve₋last:
         var x1=params.0,y1=params.1,x2=params.2,y2=params.3,x3=params.4,y3=params.5
         omgivning.addCurve(to: CGPoint(x: x1, y: y1), control1: CGPoint(x: x2, y: y2), control2: CGPoint(x: x3, y: y3))
       case bezier₋alt₋line₋close: omgivning.closePath()
       case base16₋encoded₋later₋layered₋png:
        do {
          if let (identifer,material₋text) = op.texts {
            let material₋data = try Data(base16Encoded: material₋text)
            /* guard let plate = NSImage(data: material₋data) else { throw Anomality.Image }
            let image: CGImage? = Renderimage(width: Double, height: Double) { 
             process: (NSGraphicsContext)
            }
            layer.contents = plate / * ⬷ CGImageRef alternatively NSImage. */
            /* further details written in 'CGImageSource.h'. */
          }
        }
        catch Base16EncodingError.invalidLength { print("length-error when decoding base-16 material") }
        catch Base16EncodingError.invalidByteString(_) { print("material-error when decoding base-16 material") }
        catch Base16EncodingError.invalidStringEncoding { print("utf8-string encoding error") }
        catch { print("generic handling") }
    default: print("default")
       } /* ⬷ nowdays as agreed, not strict, bezier=spaghetti-letters however are. */
    }
  }
}

class Simulationlayer: CAMetalLayer { }

func Encode(image: NSImage) -> String {
  let material₋data = image.tiffRepresentation
  let serial = material₋data!.base16EncodedString(options: [.uppercase])
  return serial
} /* ...for inclusion on web pages: base64. */


