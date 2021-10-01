/*  􀻒􀓐 enriching.swift | conveniences for built stable. */

import AppKit
import Darwin.C
import ClibTwinbeam

typealias Reference = UnsafeMutablePointer /* ⬷ a C language pointer: both access and manipulation. */
typealias Nonownings = UnsafeMutableBufferPointer /* ⬷ no manipulations of characters. */
typealias Voidstar = UnsafeMutableRawPointer /* ⬷ crossing at least two language barriers. */

func ReapTwinbeam() {
  print("hello language-analysis-and-church")
  let pid: UInt64 = 0x17
  let val: Int32 = 0x13
  /* let al: CU128 = 0x21 a․𝘬․a UInt128 */
  let y: Int32 = Details_in_C(pid,val)
  print("y is \(y)")
}

func Periodic(unresumed timer: inout DispatchSourceTimer?, 
  initial₋delay seconds₁: Double, 
  reissue₋delay milliseconds: Int, 
  fire observe: @escaping () -> Void
)
{
   let due₋initial = DispatchTime.now() + seconds₁
   timer = DispatchSource.makeTimerSource(flags: [], queue: DispatchQueue.main)
   timer?.schedule(deadline: due₋initial, repeating: .milliseconds(milliseconds), leeway: 
    .milliseconds(0))
   timer?.setEventHandler(handler: observe)
   let timer₋found = { print("timer available") }
   timer?.setRegistrationHandler(handler: timer₋found)
   timer?.resume()
}

func Utf8ToUnicode(ξ: UnsafeMutablePointer<UInt8>, bytes: Int) -> UInt32
{
  switch bytes {
  case 2:
    return UInt32(0b111111 & ξ[1]) | UInt32(0b11111 & ξ[0])<<6
  case 3:
    return UInt32(0b111111 & ξ[2]) | UInt32(0b1111 & ξ[0])<<12 | UInt32(0b111111 & ξ[1])<<6
  case 4:
    return UInt32(0b111111 & ξ[3]) | UInt32(0b111 & ξ[0])<<18 | UInt32(0b111111 & ξ[1])<<12 | 
     UInt32(0b111111 & ξ[2])<<6
  default:
    return UInt32(0xffff)
  }
}

class Interact { var process: Process?
  let p2c₋pipe=Pipe(), c2p₋pipe=Pipe() /* ⬷ /'fifo' och 'pipe' är samma sak/. */
  var output: ((Data) -> Void)?
  let maxfour = Reference<UInt8>.allocate(capacity: 4)
  
  func UnicodeToUtf8(_ uc: UInt32, maxfour bytes: inout Int) {
    /* let s = String(format: "%02x ", uc); print("converting \(s)") */
    let firstByteMark: [UInt8] = [ 0x00, 0x00, 0xc0, 0xe0, 0xf0 ]
    let mask: UInt32 = 0xbf; let mark: UInt32 = 0x80
    var Ξ=uc; if Ξ < 0x80 { bytes=1 }
    else if Ξ < 0x800 { bytes=2 }
    else if Ξ < 0x10000 { bytes=3 }
    else if Ξ < 0x0010ffff { bytes=4 }
    else { return }
    if bytes == 4 { maxfour[3] = UInt8((Ξ | mark) & mask); Ξ >>= 6 }
    if bytes >= 3 { maxfour[2] = UInt8((Ξ | mark) & mask); Ξ >>= 6 }
    if bytes >= 2 { maxfour[1] = UInt8((Ξ | mark) & mask); Ξ >>= 6 }
    if bytes >= 1 { maxfour[0] = UInt8(UInt8(truncatingIfNeeded: Ξ) | firstByteMark[bytes]) }
  }
  
  func slow₋write₋to₋child(_ unicode: UInt32) { var bytes=0
    UnicodeToUtf8(unicode, maxfour: &bytes)
    let buffer = UnsafeBufferPointer<UInt8>(start: maxfour, count: bytes)
    do { /* print("writing \(buffer.count) bytes \(buffer[0])") */
      try p2c₋pipe.fileHandleForWriting.write(contentsOf: buffer)
    } catch _ { print("unable to write to child") }
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
    c2p₋pipe.fileHandleForReading.readabilityHandler = { handle in 
      let data = handle.availableData
      if data.count > 0 { self.output?(data) } }
    do { try proc.run() } catch _ { fatalError("unable to launch process") }
    self.process = proc
  }
}

class ᴮʳTektron {
  let Unicode₋per₋tile = 8192
  var pieced₋work = Array<Reference<UInt32>>()
  var brk: Nonabsolute = 0
  private func append₋one₋tile() {
    let pointer = Reference<UInt32>.allocate(capacity: Unicode₋per₋tile)
    pieced₋work.append(pointer)
  }
  private func location(_ loc: Nonabsolute, arrayidx: inout Int, inousidx: inout Int) {
    arrayidx=Int(loc)/Unicode₋per₋tile; inousidx=Int(loc)%Unicode₋per₋tile
  }
  func append(_ unicode: UInt32) { var idx=0, slot=0
    location(brk, arrayidx: &idx, inousidx: &slot)
    if slot >= pieced₋work.count { append₋one₋tile() }
    let tile: Reference<UInt32> = pieced₋work[slot]
    tile[slot] = unicode
    self.brk += 1
  }
  func tile(﹟: Int) -> Reference<UInt32>? { if pieced₋work.count > 0 { return pieced₋work[﹟] } else { return nil } }
}

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


