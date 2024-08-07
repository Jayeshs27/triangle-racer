// #include "headers.h"
// #include <ft2build.h>
// #include FT_FREETYPE_H

// #include <map>
// #include <iostream> 
// #include <string>

// // Define a structure to hold character information
// struct Character {
//     GLuint textureID;   // ID handle of the glyph texture
//     glm::ivec2 size;    // Size of glyph
//     glm::ivec2 bearing; // Offset from baseline to left/top of glyph
//     GLuint advance;     // Offset to advance to next glyph
// };

// std::map<GLchar, Character> Characters;
// GLuint VAO, VBO;

// void LoadFont(const std::string& fontPath) {
//     // Initialize FreeType
//     FT_Library ft;
//     if (FT_Init_FreeType(&ft)) {
//         std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
//         return;
//     }

//     // Load font
//     FT_Face face;
//     if (FT_New_Face(ft, fontPath.c_str(), 0, &face)) {
//         std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
//         return;
//     }

//     // Set size to load glyphs as
//     FT_Set_Pixel_Sizes(face, 0, 48);

//     // Disable byte-alignment restriction
//     glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

//     // Load first 128 characters of ASCII set
//     for (GLubyte c = 0; c < 128; c++) {
//         // Load character glyph 
//         if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
//             std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
//             continue;
//         }
//         // Generate texture
//         GLuint texture;
//         glGenTextures(1, &texture);
//         glBindTexture(GL_TEXTURE_2D, texture);
//         glTexImage2D(
//             GL_TEXTURE_2D,
//             0,
//             GL_RED,
//             face->glyph->bitmap.width,
//             face->glyph->bitmap.rows,
//             0,
//             GL_RED,
//             GL_UNSIGNED_BYTE,
//             face->glyph->bitmap.buffer
//         );
//         // Set texture options
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//         // Now store character for later use
//         Character character = {
//             texture,
//             glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
//             glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
//             static_cast<GLuint>(face->glyph->advance.x)
//         };
//         Characters.insert(std::pair<GLchar, Character>(c, character));
//     }
//     glBindTexture(GL_TEXTURE_2D, 0);

//     // Destroy FreeType once we're finished
//     FT_Done_Face(face);
//     FT_Done_FreeType(ft);

//     // Set up VBO for texture quads
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);
//     glBindVertexArray(VAO);
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
//     glEnableVertexAttribArray(0);
//     glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);
// }

// void RenderText(unsigned int& shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) {
//     // Activate corresponding render state	
//     glUseProgram(shader);
//     glUniform3f(glGetUniformLocation(shader, "textColor"), color.x, color.y, color.z);
//     glActiveTexture(GL_TEXTURE0);
//     glBindVertexArray(VAO);

//     // Iterate through all characters
//     std::string::const_iterator c;
//     for (c = text.begin(); c != text.end(); c++) {
//         Character ch = Characters[*c];

//         GLfloat xpos = x + ch.bearing.x * scale;
//         GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

//         GLfloat w = ch.size.x * scale;
//         GLfloat h = ch.size.y * scale;
//         // Update VBO for each character
//         GLfloat vertices[6][4] = {
//             { xpos,     ypos + h,   0.0, 0.0 },            
//             { xpos,     ypos,       0.0, 1.0 },
//             { xpos + w, ypos,       1.0, 1.0 },

//             { xpos,     ypos + h,   0.0, 0.0 },
//             { xpos + w, ypos,       1.0, 1.0 },
//             { xpos + w, ypos + h,   1.0, 0.0 }           
//         };
//         // Render glyph texture over quad
//         glBindTexture(GL_TEXTURE_2D, ch.textureID);
//         // Update content of VBO memory
//         glBindBuffer(GL_ARRAY_BUFFER, VBO);
//         glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
//         glBindBuffer(GL_ARRAY_BUFFER, 0);
//         // Render quad
//         glDrawArrays(GL_TRIANGLES, 0, 6);
//         // Advance cursors for next glyph (note that advance is number of 1/64 pixels)
//         x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
//     }
//     glBindVertexArray(0);
//     glBindTexture(GL_TEXTURE_2D, 0);
// }

// int main() {
//     // Initialize GLFW
//     if (!glfwInit()) {
//         std::cout << "GLFW couldn't start" << std::endl;
//         return -1;
//     }

//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//     GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
//     if (window == NULL) {
//         std::cout << "Failed to create GLFW window" << std::endl;
//         glfwTerminate();
//         return -1;
//     }
//     glfwMakeContextCurrent(window);

//     // Initialize GLEW
//     // glewExperimental = GL_TRUE;
//     // if (glewInit() != GLEW_OK) {
//     //     std::cout << "Failed to initialize GLEW" << std::endl;
//     //     return -1;
//     // }

//     glViewport(0, 0, 800, 600);

//     // Compile and setup the shader
//     unsigned int shader = make_shaders("shaders/vertex.txt", "shaders/fragment.txt");
//     glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
//     glUseProgram(shader);
//     glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

//     // Load the font
//     LoadFont("rougeta-font/RougetaFont.ttf");

//     // Render loop
//     while (!glfwWindowShouldClose(window)) {
//         // Clear the color buffer
//         glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);

//         // Render text
//         RenderText(shader, "Hello OpenGL", 25.0f, 570.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));

//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     glfwTerminate();
//     return 0;
// }
