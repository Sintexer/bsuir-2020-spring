package com.ilyabuglakov.triangleanalyzer.service.TriangleCacher;

import com.ilyabuglakov.triangleanalyzer.model.TriangleAnalyzer.TriangleAnalyzer;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.concurrent.ConcurrentHashMap;

public interface ITriangleCacher<T> {

    T get(String key);

    T get(String s1, String s2, String s3);

    T get(int s1, int s2, int s3);

    T put(String key, T element);

    T put(String s1, String s2, String s3, T elemment);

    T put(int s1, int s2, int s3, T elemment);

    boolean contains(String key);

    boolean contains(int s1, int s2, int s3);

    boolean contains(String s1, String s2, String s3);

    String formKey(int s1, int s2, int s3);

    String formKey(String s1, String s2, String s3);
}
