/*  enriching.swift | miscellaneous helpers for Minimum. */

import AppKit

func Typeset(_ attributed: NSAttributedString, frame: NSRect, context: CGContext) -> Void
{
  let framesetter = CTFramesetterCreateWithAttributedString(attributed)
  let symbols = CFRangeMake(0,attributed.length)
  let box = frame.insetBy(dx: 3, dy: 3).offsetBy(dx: 1.5, dy: 1.5)
  let path = CGPath(rect: box.insetBy(dx: 1, dy: 1), transform: nil)
  let textframe = CTFramesetterCreateFrame(framesetter,symbols,path,nil)
  CTFrameDraw(textframe,context)
}

extension NSBezierPath {
  
  convenience init(anfang: String, font: NSFont, origin point: NSPoint)
  {
    self.init()
    let textStorage = NSTextStorage(string: anfang)
    let layoutManager = NSLayoutManager()
    textStorage.addLayoutManager(layoutManager)
    let glyphRange = layoutManager.glyphRange(forCharacterRange: NSMakeRange(0, 
     anfang.count), actualCharacterRange: nil)
    move(to: point)
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

func Renderimage(width: Int, height: Int, process: (NSGraphicsContext) -> Void) -> CGImage?
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

class Interaction { var process: Process?
  let p2c₋pipe=Pipe(), c2p₋pipe=Pipe() /* ⬷ 'fifo' and 'pipe' is similar. */
  var output: ((Data) -> Void)?
  let maxfour = UnsafeMutablePointer<UInt8>.allocate(capacity: 4)
  
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
    do { print("writing \(buffer.count) bytes of \(maxfour[0]) \(maxfour[1]) \(maxfour[2]) \(maxfour[3])")
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