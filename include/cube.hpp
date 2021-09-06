namespace glshapes {
    const float CUBE_VECTORS[] = {
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
    };
    const size_t SIZE_CUBE_VECTORS = sizeof(CUBE_VECTORS);

    const float IMAGE_CUBE_VERTICES[] = {
        // vertices needed for all faces but "top" and "bottom"
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        // vertices needed for "top" face
        -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
        // vertices needed for "bottom" face
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 0.0f, 1.0f,
    };
    const unsigned int IMAGE_CUBE_INDICES[] = {
        // front face
        0, 1, 2,
        1, 2, 3,
        // left face
        0, 1, 4,
        1, 4, 5,
        // right face
        2, 3, 6,
        3, 6, 7,
        // back face
        4, 5, 6,
        5, 6, 7,
        // top face
        4, 6, 8,
        6, 8, 9,
        // bottom face
        5, 10, 11,
        5, 7, 11
    };
    const size_t SIZE_IMAGE_CUBE_VERTICES = sizeof(IMAGE_CUBE_VERTICES);
    const size_t SIZE_IMAGE_CUBE_INDICES = sizeof(IMAGE_CUBE_INDICES);
    // const size_t SIZE_CUBE_INDICES = sizeof(CUBE_INDICES);
}
