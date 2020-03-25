package com.ilyabuglakov.triangleanalyzer.application.handlers;

import org.springframework.http.ResponseEntity;
import org.springframework.util.Assert;
import org.testng.annotations.BeforeMethod;
import org.testng.annotations.Test;
import com.ilyabuglakov.triangleanalyzer.application.exceptions.IllegalArgumentException;

public class IllegalArgumentExceptionHandlerTest {

    private IllegalArgumentExceptionHandler handler;

    @BeforeMethod
    void init(){
        handler = new IllegalArgumentExceptionHandler();
    }

    @Test
    public void testHandleExceptionWithoutMessage() {
        ResponseEntity<?> response = handler.handle( new IllegalArgumentException(""));
        Assert.notNull(response, "");
    }

    @Test
    public void testHandleExceptionWithMessage(){
        ResponseEntity<?> response = handler.handle(new IllegalArgumentException("Bad request"));
        Assert.notNull(response, "");
    }
}