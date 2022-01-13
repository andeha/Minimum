/*  enriching.swift | miscellaneous. */

import AppKit

class Interaction { var process: Process?
  let p2c₋pipe=Pipe(), c2p₋pipe=Pipe() /* ⬷ 'fifo' and 'pipe' is similar. */
  var output: ((Data) -> Void)?
  let maxfour = UnsafeMutablePointer<UInt8>.allocate(capacity: 4) /* a.k.a Reference. */
  
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