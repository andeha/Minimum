/*  machine.swift | excerpts from a selection of 'quintessential abstract machines'. */

import AppKit
import ClibTwinbeam

extension Artwork₋instruction: Hashable {
  public func hash(into hasher: inout Hasher) { hasher.combine(self.rawValue) }
  static func == (lhs: Artwork₋instruction, rhs: Artwork₋instruction) -> Bool { return lhs.rawValue == rhs.rawValue }
} /* ⬷ the c language enumeration is a wrapping 'struct' in swift. */

/*
                                                                             
    ->  o♂         skojigt∧roligt∧intressant ⟷ 'tre vis e män'     (􀇱􀤑􀈐)􀇧
  x     x  ↘︎                                                                 
   o♂            F-re-dag  13 August 2021 at 07:10:52 CEST      0c6a292b     
     <-   x o♂   F-re-dag  13 August 2021 at 07:12:11 CEST      'subjekt snabbare'
                 13 August 2021 at 07:13:29 CEST                senare i kolonn/kolumn
*/

class Artwork₋swift {
  init(text: String) { self.text = text 
   directives[width₋and₋height] = (100.0, 100.0) 
   directives[place₋origo] = (50.0, 50.0) /* case place₋center: plate.anchorpoint=CGPoint(x: 0.5, y: 0.5) */
   directives[offset₋drawing₋on] = (0.0, 0.0) }
  var directives = Dictionary<Artwork₋instruction,(Double,Double)>()
  typealias Artwork₋parameters = (Double,Double,Double,Double,Double,Double)
  struct Operation { var instruction: Artwork₋instruction; var params: Artwork₋parameters }
  var instructions = Array<Operation>()
  var size = CGSize(width: 100, height: 100)
  var text: String
}

func append₋instruction(instr: Artwork₋instruction, params: (CDouble,CDouble,CDouble,CDouble, 
 CDouble,CDouble), context: UnsafeMutableRawPointer)
{
  let artwork: Artwork₋swift? = unsafeBitCast(context, to: Artwork₋swift.self)
  if instr == width₋and₋height || instr == place₋origo || instr == offset₋drawing₋on {
    artwork?.directives[instr] = (params.0, params.1)
  } else {
    artwork?.instructions.append(Operation(instruction: instr, params: params))
  }
}

func append₋detail(instr: Artwork₋instruction, material: UnsafeMutablePointer<CChar>) { }

class Artworklayer: CALayer {
  override func draw(in: CGContext) {
    let figure: Artwork₋swift = self.contents as? Artwork₋swift
    for op in figure.instructions {
      switch op.instruction.rawValue {
       case beziercurve₋initial:
         omgivning.beginPath()
         let x=args.0,y=args.1
         CGContextMoveToPoint(omgivning,x,y)
       case beziercurve₋add:
         var cp1x=args.0,cp1y=args.1,cp2x=args.2,cp2y=args.3,x=args.4,y=args.5
         CGContextAddCurveToPoint(omgivning,cp1x,cp1y,cp2x,cp2y,x,y)
       case beziercurve₋last:
         var cp1x=args.0,cp1y=args.1,cp2x=args.2,cp2y=args.3,x=args.4,y=args.5
         CGContextAddCurveToPoint(omgivning,cp1x,cp1y,cp2x,cp2y,x,y)
       case bezier₋close: omgivning.closePath()
       case base16₋encoded₋later₋layered₋png:
        let identifer=args.0,material₋text=args.1
        do {
          let material₋data = Data(base16Encoded: material₋text)
          guard let plate = NSImage(data: material₋data) else { throw Anomality.Image }
          layer.contents = plate /* ⬷ CGImageRef alternatively NSImage. */
          /* further details written in 'CGImageSource.h'. */
        }
        catch Base16EncodingError.invalidLength { print("length-error when decoding base-16 material") }
        catch Base16EncodingError.invalidByteString() { print("material-error when decoding base-16 material") }
       } /* ⬷ nowdays as agreed, not strict, bezier=spaghetti-letters however are. */
    }
  }
}

class Drawings₁ {
  
  func interpret(bytes: Int, figure₋utf8: UnsafePointer<UInt8>, size: inout CGSize, 
    name: inout String) /* async */ throws -> CALayer
  {
    var artwork = Artwork₋swift()
    let y = Parse₋Artwork₋LL₍1₎(CInt(bytes),figure₋utf8,append₋instruction)
    var layer = Artworklayer()
    layer.contents = artwork
    let (width,height) = directives[.width₋and₋height]
    size = CGSize(width: width, height: height)
    return layer
    
  /*
  let bytes: UnsafePointer<CChar> = ... /* ⬷ NULL at end. */
  let fromwire: String? = String(utf8String: bytes) */
  /* let p = withUnsafeMutablePointer(&text) { UnsafeMutablePointer<CChar32> 
  ⬷ CChar32 a․𝘬․a String.UnicodeScalarView.Element. */
   
  }
   
  static func encode(image: NSImage) -> String {
    let serial = material₋data.base16EncodedString(options: [.uppercase])
    return serial
  }
  
  enum machinectrl { case ok; case reject }
  
 /* func c₊₊₋render₋an₋illustration(width: Double, height: Double, artwork: Artwork) -> CGImage {
    guard let image₂: CGImage = Renderimage(width: width, height: height) { 
      (context: NSGraphicsContext) -> Void in 
        let path = NSBezierPath()
        path.move(to: .init(x: 10.5, y: 10.5))
        path.line(to: .init(x: 10.5, y: 10.5))
        path.lineWidth = 1
        path.lineCapStyle = .round
        NSColor.blue.set()
        path.stroke()
    } else { return nil }
  } */
  
 /* func render₋attractive₋frame₁(width: Double, height: Double) -> CGImage? {
    let output = {
      let path = NSBezierPath()
      path.move(to: .init(x: 10.5, y: 10.5))
      path.line(to: .init(x: 10.5, y: 10.5))
      path.lineWidth = 1
      path.lineCapStyle = .round
      NSColor.blue.set()
      path.stroke()
      let string = "```\nlet x = 5\nprint(x)\n```"
      self.render(text: string, width: width, height: height) }
    return Renderimage(width: width, height: height, process: output)
  } */
  
  enum Anomality: Error { case Rendition; }
  
}

