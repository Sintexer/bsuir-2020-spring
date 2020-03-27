package com.ilyabuglakov.triangleanalyzer.service;

import org.springframework.stereotype.Service;

import java.util.concurrent.atomic.AtomicInteger;

@Service
public class RequestCounter {
    private AtomicInteger i;

    public RequestCounter(){
        i = new AtomicInteger();
    }

    public synchronized void increment(){
        //System.out.println("Counter: "+i);
        i.incrementAndGet();
    }

    public synchronized int getValue(){
        return i.get();
    }
}
