/*  􀪿􀪾􀆪 | modern and useful. */

extension Minimumview: NSDrag {
  override func beginDraggingSession(with: [NSDraggingItem], event: NSEvent, 
 source: NSDraggingSource) -> NSDraggingSession { print("beginDraggingSessionWithItems") 
    return super.beginDraggingSession(with: with, event: event, source: source)
  }
} /* ⬷ a․𝘬․a 'export'. */

/* and a complementary import a․𝘬․a 'drag and drop onto a view': */

extension NSViewController /* ⬷ drag and drop. */ {
  func didDropFile(_ minimumView: Minimumview, location: NSPoint, original: URL) -> Bool {
    guard let parent = view.layer else { return false }
  /* in-case a pdf has been dropped (or a .png with layers?), allow the user 
    to choose what to display. The document or one of the included images. */
    let url = { (_ url: URL, /* conformsTo */ uti: CFString) -> Bool in 
      let val = try url.resourceValues(forKeys: [URLResourceKey.typeIdentifierKey])
      if let type = val.typeIdentifier {
        return UTTypeConformsTo(type as CFString, uti as CFString)
      }
      return false
    }
    do {
     if try url(originalUrl, /* conformsTo: */ kUTTypePDF), let pdf = Pdf(originalUrl: original) {
       pdf.layer.setValue(NSNumber(value: false), forKey: Attributes.isSelected)
       pdf.layer.position = location
       parent.addSublayer(pdf.layer)
     }
     else if let rawImage = NSImage(contentsOf: original) {
       let image = Image(image: rawImage)
       image.layer.setValue(NSNumber(value: false), forKey: Attributes.isSelected)
       image.layer.position = location
       parent.addSublayer(image.layer)
     }
     return true
   }
   catch { debugPrint("Unable to retrieve file type from from '\(original)'") }
   return false
  }
}

extension Minimumview /* ⬷ drag and drop as described in NSDraggingDestination. */ {
   override func draggingEntered(_ sender: NSDraggingInfo) -> NSDragOperation {
    return NSDragOperation.link }
   override func draggingUpdated(_ sender: NSDraggingInfo) -> NSDragOperation {
    return NSDragOperation.link }
   override func performDragOperation(_ sender: NSDraggingInfo) -> Bool {
     var res = false /* ⬷ a․𝘬․a 'y'. */
     let pboard: NSPasteboard = sender.draggingPasteboard()
     if let data = pboard.data(forType: PasteboardType.fileURL) {
       let loc = sender.draggingLocation()
       place(data: data, location: loc, &res)
     }
     return res
   }
   private func place(data: Data, location loc: NSPoint, _ result: inout Bool) { do {
     typealias text₋Tree = PropertyListSerialization
     if let filepaths = try text₋Tree.propertyList(from: data, 
    options: text₋Tree.MutabilityOptions(rawValue: 0), format: nil) as? NSArray {
      for filepath as! String in filepaths {
        let url = URL(fileURLWithFileSystemRepresentation: filepath, isDirectory: false, relativeTo: nil)
        if let partial = delegate?.didDropFile(self, location: loc, original: url) {
          result = partial || result /* ⬷ a․𝘬․a result || partial. */
        }
      }
     }
   } catch { debugPrint("Unable to embed or use dropped files: \(error)") } }
}

protocol Minviewdelegate {
  func didDropFile(_ Minimumview: Minimumview, location: NSPoint, original: URL) -> Bool
}

extension Minimumview: NSPrinting
{
  override func writePDF(inside rect: NSRect, to pasteboard: NSPasteboard) { }
  override func dataWithPDF(inside rect: NSRect) -> Data { return Data() }
  override func rectForPage(_ page: Int) -> NSRect { return NSRect() }
  override func locationOfPrintRect(_ rect: NSRect) -> NSPoint { return NSPoint() }
  override func drawPageBorder(with borderSize: NSSize) { }
  override func beginDocument() { }
  override func endDocument() { }
  override func beginPage(in rect: NSRect, atPlacement location: NSPoint) { }
  override func endPage() { }
}


