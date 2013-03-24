#include "LXLockableTarget.h"

void LXLockableTarget::setDelegate(LXLockableTargetDelegate *delegate) {
  this->delegate = delegate;
}

LXLockableTargetDelegate *LXLockableTarget::getDelegate() {
  return delegate;
}

void LXLockableTargetDelegate::lockOn(LXLockableTarget* target) {
  target->setDelegate(this);
}
