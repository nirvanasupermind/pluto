package com.nirvanaself.pluto;

import java.util.Map;
import java.util.HashMap;

public class Env {
    public Map<String, Value> record = new HashMap<>();
    public Env parent;

    public Env() {
    }

    public Env(Env parent) {
        this.parent = parent;
    }

    public void put(String name, Value val) {
        record.put(name, val);
    } 

    public Value get(String name) {
        Value result = record.getOrDefault(name, null);

        if(result == null && parent != null) {
            return parent.get(name);
        }

        return result;
    }
}