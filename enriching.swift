/*  􀻒􀓐 enriching.swift | conveniences for built stable. */

import AppKit
import Darwin.C
import ClibTwinbeam

func ReapTwinbeam() {
  print("hello language-analysis-and-church")
  let pid: UInt64 = 0x17
  let val: Int32 = 0x13
  /* let al: CU128 = 0x21 a.k.a UInt128 */
  let y: Int32 = Details_in_C(pid,val)
  print("y is \(y)")
}

func Start(execute command: String, parameters: [String], path₋exe: String, 
 p2c p2c₋pipe: Pipe, c2p c2p₋pipe: Pipe) -> Int
{
  var args = Array<String>(); let process = path₋exe + command
  args.append(process); args.append(command); args += parameters
  let argv: [UnsafeMutablePointer<CChar>?] = args.map { $0.withCString(strdup) }
  defer { for case let arg? in argv { free(arg) } }
  let p2c₋rd₋end: FileHandle = p2c₋pipe.fileHandleForReading
  let p2c₋wr₋end: FileHandle = p2c₋pipe.fileHandleForWriting
  let c2p₋rd₋end: FileHandle = c2p₋pipe.fileHandleForReading
  let c2p₋wr₋end: FileHandle = c2p₋pipe.fileHandleForWriting
  let fd_p2c: (CInt,CInt) = ( p2c₋rd₋end.fileDescriptor, p2c₋wr₋end.fileDescriptor )
  let fd_c2p: (CInt,CInt) = ( c2p₋rd₋end.fileDescriptor, c2p₋wr₋end.fileDescriptor )
  /* ⬷ unsafe pointer to tuple is isomorph to C language array. */
  typealias Pint = UnsafeMutablePointer<Int32>
  let bufₑ: Pint? = unsafeBitCast(fd_c2p, to: Pint.self)
  let bufᵢ: Pint? = unsafeBitCast(fd_p2c, to: Pint.self)
  /* var env: (String?, String?) = ("SPAWNED_BY_TWINBEAM", nil) */
  let pid: pid_t = Twinbeam₋spawn(argv[0], argv[1], bufᵢ, bufₑ /*, F */)
 /* ⬷ a․𝘬․a if posix_spawn(&chnl.pid, argv[0], &chnl.fdactions₋child, nil, 
   argv + [nil], envir) != 0 { return -1 } / * ⬷ a․𝘬․a 'fork' and 'execlp'. */
  if pid < 0 { return -1 }
  return 0
}

/*
func Periodictimer(is timer: inout DispatchSourceTimer, 
  initial₋delay seconds₁: Double, reissue₋delay seconds₂: Double, 
  fire observe: @escaping () -> Void) {
   let due₋initial = dispatch_time(DISPATCH_TIME_NOW, seconds₁ * NSEC_PER_SEC)
   let reissue₋operation = seconds₂ * NSEC_PER_SEC
   dispatch_source_set_timer(timer,due₋initial,reissue₋operation,0.0)
   dispatch_source_set_event_handler(timer,observe)
   let timer₋found = { print("timer available") }
   dispatch_source_set_registration_handler(timer,timer₋found)
   dispatch_resume(timer)
} */

func Periodic(unresumed timer: inout DispatchSourceTimer?, 
  initial₋delay seconds₁: Double, 
  reissue₋delay milliseconds: Int, 
  fire observe: @escaping () -> Void
)
{
   let due₋initial = DispatchTime.now() + seconds₁
   timer = DispatchSource.makeTimerSource(flags: [], queue: DispatchQueue.main)
   timer?.schedule(deadline: due₋initial, repeating: .milliseconds(milliseconds), leeway: .milliseconds(0))
   timer?.setEventHandler(handler: observe)
   let timer₋found = { print("timer available") }
   timer?.setRegistrationHandler(handler: timer₋found)
   timer?.resume()
}

class Inter₋act₋and₋inte₋r₋u₋p₋t { var child: Thread? 
  
  var output: ((Data) -> Void)?
  let p2c₋pipe=Pipe(), c2p₋pipe=Pipe() /* ⬷ a․𝘬․a Fifo. */
 /* var p2c₋input, c2p₋output, c2p₋error, p2c₋ctrl, c2p₋dicipline : Pipe */
  
  func slow₋write₋to₋child(fifo: Pipe, text: String) {
    if let symbols = text.data(using: .utf8) {
      fifo.fileHandleForWriting.write(symbols)
    } else { fatalError("Unable to unwrap material (a․𝘬․a never-happens)") }
  } /* ⬷ see --<machine.swift>{parse} for correct suffixial possibly-maybe. */
  
  @objc func print₋child₋output(reader: FileHandle) {
    /* NotificationCenter:send(command₋at₋rest) */
    if let out = output { out(reader.availableData) }
  } /* ⬷ images encoded in base-64 inside run alt․ vspace. Image layered png, 
     and space is á-priori dealt! */
  
  static let command₋at₋rest = Notification.Name("command₋at₋rest")
  static let command₋finished = Notification.Name("command₋finished")
  
  var atlast₋exit: Int?
  
  func commence(execute command: String, parameters: [String], path₋exe: String, 
    out: @escaping (Data) -> Void) -> Int {
   /* int status=0; int fd_p2c[2], fd_c2p[2]; 
    if (pipe(fd_p2c) == -1 || pipe(fd_c2p) == -1) { return -1; } */
    self.output = out
    let y = Start(execute: command, parameters: parameters, path₋exe: path₋exe, 
     p2c: p2c₋pipe, c2p: c2p₋pipe)
    if y != 0 { print("Start execute failed") }
    child = Thread(target: self, selector: #selector(print₋child₋output(reader:)), 
     object: c2p₋pipe.fileHandleForReading)
    if let child = child { child.start() }
    return y
  }
  
} /* ⬷ not 'struct': 'mutating' and '@objc'. */

/* Job|12|5| He that is ready to slip with his feet is as a lamp despised in the 
 thought of him that is at ease.~ */

class Interact {
  
  var process: Process?
  let p2c₋pipe=Pipe(), c2p₋pipe=Pipe()
  var output: ((Data) -> Void)?
  
  func slow₋write₋to₋child(fifo: Pipe, text: String) {
    if let symbols = text.data(using: .utf8) {
      fifo.fileHandleForWriting.write(symbols)
    } else { fatalError("Unable to unwrap material") }
  }
  
  func commence(execute command: String, parameters: [String], path₋exe: String) {
    let url = URL(fileURLWithPath: path₋exe + command)
    let proc = Process()
    proc.executableURL = url
    proc.currentDirectoryURL = URL(fileURLWithPath: path₋exe)
    proc.arguments = parameters
    proc.standardInput = p2c₋pipe
    proc.standardOutput = c2p₋pipe
    proc.terminationHandler = { process in 
      if let c2p₋pipe = process.standardOutput as? Pipe {
        c2p₋pipe.fileHandleForReading.readabilityHandler = nil
      }
    }
    c2p₋pipe.fileHandleForReading.readabilityHandler = { fileHandle in 
      /* self.output?(fileHandle.availableData) */
      if let str = String(data: fileHandle.availableData, encoding: .utf8) {
        print(str, terminator: "")
      }
    }
    self.process = proc
    do { try proc.run() } catch _ { print("unable to launch process") }
  }
}

class ᴮʳTektron {
  let Unicode₋per₋tile = 8192
  var pieced₋work = Array<Reference<UInt32>>()
  func append₋one₋tile() {
    let pointer = Reference<UInt32>.allocate(capacity: Unicode₋per₋tile)
    pieced₋work.append(pointer)
  }
  func append(_ unicode: UInt32) { }
  func tiles(count: Int, selection: Array<Reference<UInt32>>) { }
} /* ⬷ a․𝘬․a Original. */

class ᴬᴾᴾᴸTektron {
  typealias Adjacents = ContiguousArray<Tetra𝘖rUnicode> /* ⬷ interval and scalar region. */
  var pieced₋work = Array<Adjacents>()
  var curr₋sentinel₋idx: Nonabsolute = 0
  var brk: Nonabsolute = 0
  let Unicodes₋per₋tile = 8192
  init() { append₋sentinel() }
  func append₋one₋tile() { let capacity=Unicodes₋per₋tile 
    let setup = { (buffer: inout Nonownings, initializedCount: inout Int) -> Void in 
     initializedCount=0 }
    let onetile = Adjacents(unsafeUninitializedCapacity: capacity, initializingWith: setup)
    pieced₋work.append(onetile) }
  func location(loc: Nonabsolute, arrayidx: inout Int, inousidx: inout Int) {
    let capacity=Unicodes₋per₋tile; arrayidx=Int(loc)/capacity; inousidx=Int(loc)%capacity
  } /* ⬷ suffixial binding of interest after a coupe, 𝘦․𝘨 'loc divmod capacity, arrayidx=rah, inousidx=ral'. */
  func append₋various(_ taltu: Tetra𝘖rUnicode) {
    var idx: Int = 0; var slot: Int = 0
    location(loc: brk, arrayidx: &idx, inousidx: &slot)
    if slot >= pieced₋work.count { append₋one₋tile() }
    var array = pieced₋work[idx]
    array.append(taltu)
    self.brk += 1 }
  func append₋one₋unicode(uc: CChar32) {
    let elem = Tetra𝘖rUnicode(uc: uc.value)
    append₋various(elem)
  }
  func append₋sentinel() {
    curr₋sentinel₋idx = self.brk
    let elem = Tetra𝘖rUnicode(count: -1)
    append₋various(elem)
  }
  func fill₋in₋sentinel() {
    var idx: Int = 0; var slot: Int = 0
    location(loc: curr₋sentinel₋idx, arrayidx: &idx, inousidx: &slot)
    let unicode₋count = self.brk - curr₋sentinel₋idx - 1
    var carray = pieced₋work[idx]
    carray[slot].count = Int32(unicode₋count)
  }
  func baseaddress(tile: Int) -> Reference<Tetra𝘖rUnicode>? {
    return self.pieced₋work[tile]._baseAddressIfContiguous
  } /* ⬷ when crossing to C the ContigousArray is implicity casted to 
 an UnsafeMutablePointer<Tetra𝘖rUnicode>. */
} /* ⬷ a․𝘬․a 􀠧-Sergeant. See --<Kiddle.hpp> for early attempt. */

class Quilt {
  func graphics₋begin() { print("graphics begin") }
  func graphics₋ended() { print("graphics ended") }
} /* ⬷ a․𝘬․a 􀠧􀠧􀠧-Fanjunkare. */

extension NSBezierPath {
  
  convenience init(anfang: String, font: NSFont, frame rect: NSRect)
  {
    self.init()
    let textStorage = NSTextStorage(string: anfang)
    let layoutManager = NSLayoutManager()
    textStorage.addLayoutManager(layoutManager)
    let glyphRange = layoutManager.glyphRange(forCharacterRange: NSMakeRange(0, 
     anfang.count), actualCharacterRange: nil)
    move(to: NSPoint(x: 20.0, y: 20.0))
    for i in glyphRange.location..<glyphRange.location + glyphRange.length {
      let g = layoutManager.glyph(at: i, isValidIndex: nil)
      self.append(withCGGlyph: CGGlyph(g), in: font)
    }
  } /* ⬷ for bear from 'anfang: Character'. */
  
  var cgPath: CGPath
  {
    let path = CGMutablePath()
    var points = [CGPoint](repeating: .zero, count: 3)
    
    for i in 0 ..< self.elementCount {
      let type = self.element(at: i, associatedPoints: &points)
      switch type {
      case .moveTo:
        path.move(to: points[0])
      case .lineTo:
        path.addLine(to: points[0])
      case .curveTo:
        path.addCurve(to: points[2], control1: points[0], control2: points[1])
      case .closePath:
        path.closeSubpath()
      @unknown default: print("cgpath: unknown default")
      }
    }
    
    return path
  }
  
}

func Utf8ToUnicode(ξ: UnsafeMutablePointer<UInt8>, bytes: Int) -> UInt32
{
  switch bytes {
  case 2:
    return UInt32(0b111111 & ξ[1]) | UInt32(0b11111 & ξ[0])<<6
  case 3:
    return UInt32(0b111111 & ξ[2]) | UInt32(0b1111 & ξ[0])<<12 | UInt32(0b111111 & ξ[1])<<6
  case 4:
    return UInt32(0b111111 & ξ[3]) | UInt32(0b111 & ξ[0])<<18 | UInt32(0b111111 & ξ[1])<<12 | UInt32(0b111111 & ξ[2])<<6
  default:
    return UInt32(0xffff)
  }
}

class Trackpad {
  struct Spatial { var instant: TimeInterval; var proximity₋spatial: NSPoint }
  struct Pressure { var instant: TimeInterval; var pressure: Double }
  struct Segment { var ended: Bool; var samples: Array<Spatial> }
  struct Point { /* var ended: Bool; */ var samples: Array<Pressure> }
  let feedback = NSAlignmentFeedbackFilter()
  var tracklines = Dictionary<NSView.Trek,Segment>()
  var pressures = Dictionary<NSView.Trek,Point>()
  
  func log₋rectangle(with event: NSEvent, view: NSView, initial: Bool) {
    let instant: TimeInterval = event.timestamp
    let pressure = event.pressure
    let ovals: Set<NSTouch> = event.touches(matching: .moved, in: view)
    for oval in ovals {
      let identity = NSView.Trek(ident: oval.identity)
     /* let location₁ = event.locationInWindow
     let location₂ = self.superview.convertPoint(location₁, fromView: nil) */
      let normalized = oval.normalizedPosition
      let sample = Spatial(instant: instant, proximity₋spatial: normalized)
      if var spatiala = self.tracklines[identity] {
        spatiala.samples.append(sample)
        /* ⬷ found occurrence in dictionary. */
      } else {
        let initial = Spatial(instant: instant, proximity₋spatial: normalized)
        let array = [ initial ]
        let initial₋alt₋suffix = Segment(ended: false, samples: array)
        self.tracklines[identity] = initial₋alt₋suffix
        /* ⬷ first occurrence added. */
      }
      /* let spatiala: Segment = tracklines[identity]
      let initial₋alt₋suffix: Array<Spatial> = [
       Spatial(instant: instant, proximity₋spatial: normalized, pressure: pressure)
      ] */
      
      if initial { print("interaction-began") }
      else { print("interaction-moved at \(normalized)") }
    }
  }
  
  func hapticFeedback(_ view: NSView) { var prepared = [NSAlignmentFeedbackToken]() 
    if let token = self.feedback.alignmentFeedbackTokenForHorizontalMovement(in: 
     view, previousX: 0.0, alignedX: 1.0, defaultX: 2.0) { prepared += [token] }
    self.feedback.performFeedback(prepared, performanceTime: .now) }
  func entered(with event: NSEvent, in view: NSView) { self.hapticFeedback(view); print("entered") }
  func exited(with event: NSEvent, in view: NSView) { self.hapticFeedback(view); print("exited") }
  func cancelled(with event: NSEvent, view: NSView) {
    let instant: TimeInterval = event.timestamp
    let ovals: Set<NSTouch> = event.touches(matching: .moved, in: view)
    for oval in ovals {
      let identity = NSView.Trek(ident: oval.identity)
      print("\(instant): must-cancel.")
    }
  }
  func ended(with event: NSEvent, view: NSView) {
    let instant: TimeInterval = event.timestamp
    let ovals: Set<NSTouch> = event.touches(matching: .moved, in: view)
    for oval in ovals {
      let identity = NSView.Trek(ident: oval.identity)
      print("\(instant): not-ended.")
    }
  }
  func pressure(with event: NSEvent) {
    let instant: TimeInterval = event.timestamp
    let pressure = event.pressure
/*    let ovals: Set<NSTouch> = event.touches(matching: .moved, in: view)
    for oval in ovals {
      if var spatiala = self.pressures[identity] {
      } else { print("non-existing old") 
      }
      print("\(instant): pressure is \(pressure)")
    } */
  }
}

extension NSView {
  struct Trek : Hashable { var ident: NSObjectProtocol & NSCopying 
    init(ident: NSObjectProtocol & NSCopying) { self.ident = ident }
    func hash(into hasher: inout Hasher) { return hasher.combine(ident.hash) }
    static func == (lhs: Trek, rhs: Trek) -> Bool { return lhs.ident.isEqual(rhs.ident) }
  }
}

func Renderimage(width: Int, height: Int, 
 process: (NSGraphicsContext) -> Void) -> CGImage?
{
  guard let plate = CGContext(data: nil, width: width, height: height, 
    bitsPerComponent: 8, bytesPerRow: 0, 
    space: CGColorSpace(name: CGColorSpace.sRGB)!, 
    bitmapInfo: CGImageAlphaInfo.premultipliedLast.rawValue) else { return nil }
  let ns₋plate = NSGraphicsContext(cgContext: plate, flipped: true)
  guard let previous = NSGraphicsContext.current else { return nil }
  previous.cgContext.saveGState(); NSGraphicsContext.current = ns₋plate
  ns₋plate.cgContext.beginTransparencyLayer(auxiliaryInfo: nil)
  do { process(ns₋plate) }
  ns₋plate.cgContext.endTransparencyLayer()
  /* NSGraphicsContext.current = nil */
  previous.cgContext.restoreGState()
  return plate.makeImage()
}

extension NSMenuItem {
  convenience init(title string: String, target: AnyObject = self as AnyObject, 
    action selector: Selector?, keyEquivalent charCode: String, 
    modifier: NSEvent.ModifierFlags = .command) {
   self.init(title: string, action: selector, keyEquivalent: charCode)
   keyEquivalentModifierMask = modifier
   self.target = target
  }
  convenience init(title string: String, submenuItems: [NSMenuItem]) {
    self.init(title: string, action: nil, keyEquivalent: "")
    self.submenu = NSMenu()
    self.submenu?.items = submenuItems
  }
}

extension NotificationCenter {
  static func send(_ key: Notification.Name, object: Any?) {
   self.default.post(name: key, object: object) }
  static func receive(_ key: Notification.Name, instance: Any, 
 selector: Selector) { self.default.addObserver(instance, 
   selector: selector, name: key, object: nil) }
}

class default₋Windowdelegate: NSObject, NSWindowDelegate {
func windowDidEndLiveResize(_ notification: Notification) { print("windowDidEndLiveResize") }
/* func windowWillClose(_ notification: Notification) { print("window will close") } */
func windowWillClose(_ notification: Notification) { print("terminate"); NSApplication.shared.terminate(0) }
func windowShouldClose(_ sender: NSWindow) -> Bool { print("windowShouldClose"); return true }
func windowWillStartLiveResize(_ notification: Notification) { print("windowWillStartLiveResize") }
func windowWillResize(_ sender: NSWindow, to frameSize: NSSize) -> NSSize { return frameSize }
func windowDidResize(_ notification: Notification) { print("window resize") }
func windowWillMiniaturize(_ notification: Notification) { print("windowWillMiniaturize") }
func windowDidDeminiaturize(_ notification: Notification) { print("windowDidDeminiaturize") }
func windowDidMiniaturize(_ notification: Notification) { print("window miniaturize") }
func windowWillUseStandardFrame(_ window: NSWindow, defaultFrame newFrame: NSRect) -> NSRect { return newFrame }
func windowShouldZoom(_ window: NSWindow, toFrame newFrame: NSRect) -> Bool { return true }
func windowDidChangeScreen(_ notification: Notification) { print("windowDidChangeScreen") }
func windowDidChangeScreenProfile(_ notification: Notification) { print("windowDidChangeScreenProfile") }
func windowDidChangeBackingProperties(_ notification: Notification) { print("windowDidChangeBackingProperties") }
func windowDidBecomeKey(_ notification: Notification) { print("windowDidBecomeKey") }
func windowDidResignKey(_ notification: Notification) { print("windowDidResignKey") }
func windowDidBecomeMain(_ notification: Notification) { print("windowDidBecomeMain") }
func windowDidResignMain(_ notification: Notification) { print("windowDidResignMain") }
func windowWillReturnFieldEditor(_ sender: NSWindow, to client: Any?) -> Any? { return client }
func windowDidUpdate(_ notification: Notification) { print("windowDidUpdate") }
func windowDidExpose(_ notification: Notification) { print("windowDidExpose") }
func windowDidChangeOcclusionState(_ notification: Notification) { print("windowDidChangeOcclusionState") } /* ⬷ app-nap. */
func window(_ window: NSWindow, shouldDragDocumentWith event: NSEvent, from dragImageLocation: NSPoint, with pasteboard: NSPasteboard) -> Bool { return false }
func window(_ window: NSWindow, shouldPopUpDocumentPathMenu menu: NSMenu) -> Bool { return false }
func window(_ window: NSWindow, willEncodeRestorableState state: NSCoder) { print("willEncodeRestorableState") }
func window(_ window: NSWindow, didDecodeRestorableState state: NSCoder) { print("didDecodeRestorableState") }
func window(_ window: NSWindow, willResizeForVersionBrowserWithMaxPreferredSize maxPreferredFrameSize: NSSize, maxAllowedSize maxAllowedFrameSize: NSSize) -> NSSize { return maxAllowedFrameSize }
func windowWillEnterVersionBrowser(_ notification: Notification) { print("windowWillEnterVersionBrowser") }
func windowDidEnterVersionBrowser(_ notification: Notification) { print("windowDidEnterVersionBrowser") }
func windowWillExitVersionBrowser(_ notification: Notification) { print("windowWillExitVersionBrowser") }
func windowDidExitVersionBrowser(_ notification: Notification) { print("windowDidExitVersionBrowser") }
}

/* play-and-listen-i --<Pigments>--<Antares>--<1 left = 2SINE SWEEPS>--<A D G>. */


