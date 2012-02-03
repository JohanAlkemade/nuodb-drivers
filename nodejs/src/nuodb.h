// Copyright 2012 NuoDB, Inc.
#ifndef SRC_NUODB_H_
#define SRC_NUODB_H_

#include "./node-db/node_defs.h"
#include "./node-db/binding.h"
#include "./connection.h"
#include "./query.h"

namespace node_db_nuodb {
class NuoDB : public node_db::Binding {
    public:
        static void Init(v8::Handle<v8::Object> target);

    protected:
        static v8::Persistent<v8::FunctionTemplate> constructorTemplate;

        NuoDB();
        ~NuoDB();
        static v8::Handle<v8::Value> New(const v8::Arguments& args);
        v8::Handle<v8::Value> set(const v8::Local<v8::Object> options);
        v8::Persistent<v8::Object> createQuery() const;
};
}

#endif  // SRC_NUODB_H_
