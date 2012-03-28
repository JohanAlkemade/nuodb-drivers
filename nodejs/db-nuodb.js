/****************************************************************************
 * Copyright (c) 2012, NuoDB, Inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of NuoDB, Inc. nor the names of its contributors may
 *       be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NUODB, INC. BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ****************************************************************************/

/**
 * Require bindings native binary
 *
 * @ignore
 */
var EventEmitter = require('events').EventEmitter,
    binding;

try {
    binding = require("./build/default/nuodb_bindings");
} catch(error) {
    binding = require("./build/Release/nuodb_bindings");
}

function extend(target, source) {
    for (var k in source.prototype) {
        target.prototype[k] = source.prototype[k];
    }
    return target;
}

var BaseEventEmitter = extend(function() {}, EventEmitter);
BaseEventEmitter.prototype.emit = function() {
    var type = arguments[0];
    if (type === 'error' && (!this._events || !this._events.error || (Array.isArray(this._events.error) && !this._events.error.length))) {
        // Silently allow unattached error events
        return;
    }
    return EventEmitter.prototype.emit.apply(this, arguments);
}

exports.Query = extend(binding.Query, BaseEventEmitter);
exports.Database = extend(binding.NuoDB, BaseEventEmitter);
