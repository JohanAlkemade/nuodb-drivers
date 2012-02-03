// Copyright 2012 NuoDB, Inc.
#ifndef SRC_QUERY_H_
#define SRC_QUERY_H_

#include "./node-db/node_defs.h"
#include "./node-db/query.h"

namespace node_db_nuodb {
class Query : public node_db::Query {
    public:
        static v8::Persistent<v8::FunctionTemplate> constructorTemplate;
        static void Init(v8::Handle<v8::Object> target);

    protected:
        static v8::Handle<v8::Value> New(const v8::Arguments& args);
        static v8::Handle<v8::Value> Limit(const v8::Arguments& args);
};
}

#endif  // SRC_QUERY_H_
