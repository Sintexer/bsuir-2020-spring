package com.ilyabuglakov.triangleanalyzer.service.TriangleCacher;

import com.ilyabuglakov.triangleanalyzer.model.TriangleAnalyzer.ITriangleAnalyzer;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.stereotype.Service;

import java.util.concurrent.ConcurrentHashMap;

@Service
public class TriangleCacher<T extends ITriangleAnalyzer> implements ITriangleCacher<T> {

    private static Logger logger = LogManager.getLogger(TriangleCacher.class);

    private ConcurrentHashMap<String, T> repository;

    public TriangleCacher() {
        repository = new ConcurrentHashMap<>();
    }

    public T get(String key) {
        logger.info("Returned existing response from cache with key={}", key);
        return repository.get(key);
    }

    public T get(String s1, String s2, String s3) {
        return get(formKey(s1, s2, s3));
    }

    public T get(int s1, int s2, int s3) {
        return get(formKey(s1, s2, s3));
    }

    public T put(String key, T element) {
        logger.info("Cached new element with key={}", key);
        repository.put(key, element);
        return element;
    }

    public T put(String s1, String s2, String s3, T element) {
        return put(formKey(s1, s2, s3), element);
    }

    public T put(int s1, int s2, int s3, T element) {
        return put(formKey(s1, s2, s3), element);
    }

    public boolean contains(String key) {
        return repository.containsKey(key);
    }

    public boolean contains(int s1, int s2, int s3) {
        return contains(formKey(s1, s2, s3));
    }

    public boolean contains(String s1, String s2, String s3) {
        return contains(formKey(s1, s2, s3));
    }

    public boolean contains(T element){
        return repository.contains(element);
    }

    public String formKey(int s1, int s2, int s3) {
        return String.format("%d-%d-%d", s1, s2, s3);
    }

    public String formKey(String s1, String s2, String s3) {
        return String.format("%s-%s-%s", s1, s2, s3);
    }
}
