// Copyright 2012 NuoDB, Inc.
#include "./node-db/binding.h"
#include "./nuodb.h"
#include "./query.h"

extern "C" {
    void init(v8::Handle<v8::Object> target) {
        node_db::EventEmitter::Init();
        node_db_nuodb::NuoDB::Init(target);
        node_db_nuodb::Query::Init(target);
    }

    NODE_MODULE(nuodb_bindings, init);
}
