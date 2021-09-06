namespace glshapes {
    const float BUCEPHALUS_VECTORS[] = {
        // front face of inner cube
        -0.5f,  0.5f,  0.5f,          // 0
        -0.5f, -0.5f,  0.5f,          // 1
         0.5f,  0.5f,  0.5f,          // 2
         0.5f, -0.5f,  0.5f,          // 3
         // rear face of inner cube
        -0.5f,  0.5f, -0.5f,          // 4
        -0.5f, -0.5f, -0.5f,          // 5
         0.5f,  0.5f, -0.5f,          // 6
         0.5f, -0.5f, -0.5f,          // 7
         // "pyramid face" vectors
         0.75f,   0.00f,   0.00f,    // 8
        -0.75f,   0.00f,   0.00f,    // 9
         0.00f,   0.75f,   0.00f,    // 10
         0.00f,  -0.75f,   0.00f,    // 11
         0.00f,   0.00f,   0.75f,    // 12
         0.00f,   0.00f,  -0.75f,    // 13
    };
    const size_t SIZE_BUCEPHALUS_VECTORS = sizeof(BUCEPHALUS_VECTORS);
    const unsigned int BUCEPHALUS_INDICES[] = {
        // front face
        0, 1, 12,
        0, 2, 12,
        3, 1, 12,
        3, 2, 12,
        // rear face
        4, 5, 13,
        4, 6, 13,
        7, 5, 13,
        7, 6, 13,
        // right face
        2, 3, 8, 
        2, 6, 8,
        7, 3, 8,
        7, 6, 8,
        // left face
        0, 1, 9, 
        0, 4, 9,
        5, 1, 9,
        5, 4, 9,
        // top face
        0, 4, 10, 
        0, 2, 10,
        6, 4, 10,
        6, 2, 10,
        // bottom face
        1, 5, 11, 
        1, 3, 11,
        7, 5, 11,
        7, 3, 11,
    };
    const size_t SIZE_BUCEPHALUS_INDICES = sizeof(BUCEPHALUS_INDICES);
}
