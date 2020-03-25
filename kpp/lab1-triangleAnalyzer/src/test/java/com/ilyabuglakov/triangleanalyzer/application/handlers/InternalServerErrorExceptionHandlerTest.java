package com.ilyabuglakov.triangleanalyzer.application.handlers;

import org.springframework.http.ResponseEntity;
import org.springframework.util.Assert;
import org.testng.annotations.BeforeMethod;
import org.testng.annotations.Test;
import com.ilyabuglakov.triangleanalyzer.application.exceptions.InternalServerErrorException;

public class InternalServerErrorExceptionHandlerTest {

    private InternalServerErrorExceptionHandler handler;

    @BeforeMethod
    void init(){
        handler = new InternalServerErrorExceptionHandler();
    }

    @Test
    public void testHandleExceptionWithoutMessage() {
        ResponseEntity<?> response = handler.handle( new InternalServerErrorException(""));
        Assert.notNull(response, "");
    }

    @Test
    public void testHandleExceptionWithMessage(){
        ResponseEntity<?> response = handler.handle(new InternalServerErrorException("Internal Server Error"));
        Assert.notNull(response, "");
    }
}