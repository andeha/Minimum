/* 􀻒 Extensions.swift | conveniences for stable built-ins. */

import Foundation

extension NotificationCenter {
  
  static func send(_ key: Notification.Name) {
    self.default.post(name: key, object: nil)
  }
  
  static func receive(_ key: Notification.Name, 
   instance: Any, selector: Selector) { self.default.addObserver(instance, 
   selector: selector, name: key, object: nil) }
  
}

extension Notification.Name {
  static let preferencesChanged = Notification.Name("preferencesChanged")
}


