// Copyright 2012 NuoDB, Inc. <cadmin@nuodb.com>
#include "./query.h"

v8::Persistent<v8::FunctionTemplate> node_db_nuodb::Query::constructorTemplate;

void node_db_nuodb::Query::Init(v8::Handle<v8::Object> target) {
    v8::HandleScope scope;

    v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(New);

    constructorTemplate = v8::Persistent<v8::FunctionTemplate>::New(t);
    constructorTemplate->InstanceTemplate()->SetInternalFieldCount(1);

    node_db::Query::Init(target, constructorTemplate);

    NODE_ADD_PROTOTYPE_METHOD(constructorTemplate, "limit", Limit);

    target->Set(v8::String::NewSymbol("Query"), constructorTemplate->GetFunction());
}

v8::Handle<v8::Value> node_db_nuodb::Query::New(const v8::Arguments& args) {
    v8::HandleScope scope;

    node_db_nuodb::Query* query = new node_db_nuodb::Query();
    if (query == NULL) {
        THROW_EXCEPTION("Can't create query object")
    }

    if (args.Length() > 0) {
        v8::Handle<v8::Value> set = query->set(args);
        if (!set.IsEmpty()) {
            return scope.Close(set);
        }
    }

    query->Wrap(args.This());

    return scope.Close(args.This());
}

v8::Handle<v8::Value> node_db_nuodb::Query::Limit(const v8::Arguments& args) {
    v8::HandleScope scope;

    if (args.Length() > 1) {
        ARG_CHECK_UINT32(0, offset);
        ARG_CHECK_UINT32(1, rows);
    } else {
        ARG_CHECK_UINT32(0, rows);
    }

    node_db_nuodb::Query *query = node::ObjectWrap::Unwrap<node_db_nuodb::Query>(args.This());
    assert(query);

    std::string currentSql = query->sql.str();

    query->sql.str("");
    query->sql.clear();

    uint32_t start = args[0]->ToInt32()->Value(), end = 0;
    if (args.Length() > 1) {
        end = args[1]->ToInt32()->Value();
    } else if (start > 1) {
        end = start;
        start = 1;
    }

    query->sql << "SELECT * FROM (" << currentSql << ") WHERE ROWNUM";
    if (start > 1 || end > 0) {
        query->sql << " BETWEEN " << start << " AND " << end;
    } else {
        query->sql << "=" << start;
    }

    return scope.Close(args.This());
}
