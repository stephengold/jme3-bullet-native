/*
 * Copyright (c) 2019-2021 jMonkeyEngine
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * * Neither the name of 'jMonkeyEngine' nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
package com.jme3.bullet.collision.shapes.infos;

import com.jme3.bullet.NativePhysicsObject;
import com.jme3.math.Vector3f;
import com.jme3.util.BufferUtils;
import java.nio.ByteBuffer;
import java.nio.FloatBuffer;
import java.nio.IntBuffer;
import java.nio.ShortBuffer;
import java.util.logging.Level;
import java.util.logging.Logger;
import jme3utilities.Validate;

/**
 * An indexed triangle mesh based on Bullet's btIndexedMesh. Immutable.
 *
 * @author Stephen Gold sgold@sonic.net
 */
public class IndexedMesh extends NativePhysicsObject {
    // *************************************************************************
    // constants and loggers

    /**
     * number of bytes in a float
     */
    final private static int floatBytes = 4;
    /**
     * number of bytes in an int
     */
    final private static int intBytes = 4;
    /**
     * number of axes in a vector
     */
    final private static int numAxes = 3;
    /**
     * number of vertices per triangle
     */
    final private static int vpt = 3;
    /**
     * message logger for this class
     */
    final public static Logger logger
            = Logger.getLogger(IndexedMesh.class.getName());
    // *************************************************************************
    // fields

    /**
     * configured position data: 3 floats per vertex (not null, direct, never
     * flipped)
     */
    final private FloatBuffer vertexPositions;
    /**
     * configured index data: 3 ints per triangle (not null, direct, never
     * flipped)
     */
    final private IntBuffer indices;
    /**
     * configured bytes per triangle in the index buffer (12)
     */
    final private int indexStride;
    /**
     * configured number of triangles in the mesh (&ge;0)
     */
    final private int numTriangles;
    /**
     * configured number of vertices in the mesh (&ge;0)
     */
    final private int numVertices;
    /**
     * configured bytes per vertex in the position buffer (12)
     */
    final private int vertexStride;
    // *************************************************************************
    // constructors

    /**
     * Instantiate an IndexedMesh based on the specified positions and indices.
     *
     * @param positionArray (not null, unaffected)
     * @param indexArray (not null, unaffected, length a multiple of 3)
     */
    public IndexedMesh(Vector3f[] positionArray, int[] indexArray) {
        Validate.nonNull(positionArray, "position array");
        Validate.nonNull(indexArray, "index array");
        int numIndices = indexArray.length;
        Validate.require(numIndices % vpt == 0, "length a multiple of 3");

        numVertices = positionArray.length;
        vertexPositions = BufferUtils.createFloatBuffer(positionArray);
        vertexStride = numAxes * floatBytes;

        numTriangles = numIndices / vpt;
        indices = BufferUtils.createIntBuffer(indexArray);
        indexStride = vpt * intBytes;

        createMesh();
    }
    // *************************************************************************
    // new methods exposed

    /**
     * Copy the triangle indices.
     *
     * @return a new, direct, unflipped buffer
     */
    public IntBuffer copyIndices() {
        int numInts = indices.capacity();
        IntBuffer result = BufferUtils.createIntBuffer(numInts);
        for (int bufPos = 0; bufPos < numInts; ++bufPos) {
            int tmpIndex = indices.get(bufPos);
            result.put(tmpIndex);
        }

        return result;
    }

    /**
     * Copy the vertex positions to a new buffer.
     *
     * @return a new, direct, unflipped buffer
     */
    public FloatBuffer copyVertexPositions() {
        int numFloats = vertexPositions.capacity();
        FloatBuffer result = BufferUtils.createFloatBuffer(numFloats);
        for (int bufPos = 0; bufPos < numFloats; ++bufPos) {
            float tmpFloat = vertexPositions.get(bufPos);
            result.put(tmpFloat);
        }

        return result;
    }

    /**
     * Count how many triangles are in this mesh.
     *
     * @return the count (&ge;0)
     */
    public int countTriangles() {
        assert numTriangles >= 0 : numTriangles;
        return numTriangles;
    }

    /**
     * Count how many vertices are in this mesh.
     *
     * @return the count (&ge;0)
     */
    public int countVertices() {
        assert numVertices >= 0 : numVertices;
        return numVertices;
    }
    // *************************************************************************
    // Java private methods

    /**
     * Create a new btIndexedMesh using the current configuration.
     */
    private void createMesh() {
        assert vertexStride == 12 : vertexStride;
        assert indexStride == 12 : indexStride;

        long meshId = createInt(indices, vertexPositions, numTriangles,
                numVertices, vertexStride, indexStride);
        setNativeId(meshId);

        logger.log(Level.FINE, "Created {0}", this);
    }

    /**
     * Free the identified tracked native object. Invoked by reflection.
     *
     * @param meshId the native identifier (not zero)
     */
    private static void freeNativeObject(long meshId) {
        assert meshId != 0L;
        finalizeNative(meshId);
    }
    // *************************************************************************
    // native private methods

    native private static long createByte(ByteBuffer indices,
            FloatBuffer vertexPositions, int numTriangles, int numVertices,
            int vertexStride, int indexStride);

    native private static long createInt(IntBuffer indices,
            FloatBuffer vertexPositions, int numTriangles, int numVertices,
            int vertexStride, int indexStride);

    native private static long createShort(ShortBuffer indices,
            FloatBuffer vertexPositions, int numTriangles, int numVertices,
            int vertexStride, int indexStride);

    native private static void finalizeNative(long meshId);
}
