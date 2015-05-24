#include "LockableTarget.h"

void LockableTarget::setDelegate(LockableTargetDelegate* delegate) {
    this->delegate = delegate;
}

LockableTargetDelegate* LockableTarget::getDelegate() {
    return delegate;
}

void LockableTargetDelegate::lockOn(LockableTarget* target, const Transform& transform) {
    target->setDelegate(this);
}

void LockableTargetDelegate::stopLock(LockableTarget* target) {
    target->setDelegate(0);
}
