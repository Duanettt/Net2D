#include "TileMapEditor.h"
#include "../Graphics/Renderer.h"

TileMapEditor::TileMapEditor(Tilemap* mp, Tileset* ts, glm::vec2 cs) : map(mp), tileset(ts), currentTile(0), isEditing(false), gridSize(cs), editorKeys({
            GLFW_KEY_E,           // Toggle editor
            GLFW_KEY_LEFT,        // Previous tile
            GLFW_KEY_RIGHT,       // Next tile
            GLFW_KEY_DELETE       // Clear tile
            })
{

}

void TileMapEditor::handle_input(GLFWwindow* window, double mouseX, double mouseY)
{
    int gridX = static_cast<int>(mouseX / gridSize.x);
    int gridY = static_cast<int>(mouseY / gridSize.y);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        map->set_tile(gridX, gridY, currentTile);  // Note: using currentTile instead of 0
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        map->clear_tile(gridX, gridY);
    }
}

void TileMapEditor::set_current_tile(int tileIndex)
{
	currentTile = tileIndex;
}

//void TileMapEditor::setup_grid()
//{
//    // Draw vertical lines
//    for (int x = 0; x <= map->get_width(); x++) {
//        float xPos = x * gridSize.x;
//        globals.r->setup_line_renderer(
//            glm::vec2(xPos, 0),
//            glm::vec2(xPos, map->get_height() * gridSize.y),
//            glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)
//        );
//    }
//
//    // Draw horizontal lines
//    for (int y = 0; y <= map->get_height(); y++) {
//        float yPos = y * gridSize.y;
//        globals.r->setup_line_renderer(
//            glm::vec2(0, yPos),
//            glm::vec2(map->get_width() * gridSize.x, yPos),
//            glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)
//        );
//    }
//}

//void TileMapEditor::draw_grid()
//{
//    globals.r->draw_line();
//}

//void TileMapEditor::render()
//{
//    if (!editorMode || !map) return;
//
//    globals.r->drawTile(currentTileIndex, glm::vec2(0, 0), glm::vec2(32, 32));
//
//    draw_grid();
//}

void TileMapEditor::process_editor_input()
{
    // Toggle editor mode
    static bool eKeyWasDown = false;
    bool eKeyIsDown = editorKeys.get_is_key_down(GLFW_KEY_E);
    if (eKeyIsDown && !eKeyWasDown) {
        editorMode = !editorMode;
        std::cout << "Editor mode: " << (editorMode ? "ON" : "OFF") << std::endl;
    }
    eKeyWasDown = eKeyIsDown;

    if (!editorMode || !map) return;

    // Handle tile selection with arrow keys
    static bool leftKeyWasDown = false;
    static bool rightKeyWasDown = false;

    bool leftKeyIsDown = editorKeys.get_is_key_down(GLFW_KEY_LEFT);
    bool rightKeyIsDown = editorKeys.get_is_key_down(GLFW_KEY_RIGHT);



    if (leftKeyIsDown && !leftKeyWasDown) {
        currentTileIndex = std::max(0, currentTileIndex - 1);
        std::cout << "Selected tile: " << currentTileIndex << std::endl;
    }
    if (rightKeyIsDown && !rightKeyWasDown) {
        int maxTiles = globals.r->get_tileset()->get_columns() *
            globals.r->get_tileset()->get_rows() - 1;
        currentTileIndex = std::min(maxTiles, currentTileIndex + 1);
        std::cout << "Selected tile: " << currentTileIndex << std::endl;
    }

    leftKeyWasDown = leftKeyIsDown;
    rightKeyWasDown = rightKeyIsDown;

}

void TileMapEditor::setup_grid()
{
    std::vector<float> gridVertices;

    // Calculate stepping in NDC coordinates
    float xStep = 2.0f / static_cast<float>(map->get_width());
    float yStep = 2.0f / static_cast<float>(map->get_height());

    // Vertical lines
    for (int x = 0; x <= map->get_width(); x++) {
        float xPos = (x * xStep) - 1.0f;  // Convert to NDC (-1 to 1)
        // Bottom point
        gridVertices.push_back(xPos);
        gridVertices.push_back(-1.0f);
        // Top point
        gridVertices.push_back(xPos);
        gridVertices.push_back(1.0f);
    }

    // Horizontal lines
    for (int y = 0; y <= map->get_height(); y++) {
        float yPos = (y * yStep) - 1.0f;  // Convert to NDC (-1 to 1)
        // Left point
        gridVertices.push_back(-1.0f);
        gridVertices.push_back(yPos);
        // Right point
        gridVertices.push_back(1.0f);
        gridVertices.push_back(yPos);
    }

    // Generate and bind VAO/VBO for grid lines
    if (gridVAO == 0) {
        glGenVertexArrays(1, &gridVAO);
    }
    if (gridVBO == 0) {
        glGenBuffers(1, &gridVBO);
    }

    glBindVertexArray(gridVAO);
    glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
    glBufferData(GL_ARRAY_BUFFER, gridVertices.size() * sizeof(float), gridVertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    numGridLines = gridVertices.size() / 2;  // Each vertex has 2 components (x,y)
}


void TileMapEditor::draw_grid()
{
    //std::cout << "[DEBUG] Drawing of grid" << std::endl;

    if (!editorMode) return;

    ResourceManager& rm = ResourceManager::get_instance();
    Shader* lineShader = rm.get_shaders("lines");

    lineShader->use();
    lineShader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    glBindVertexArray(gridVAO);
    glDrawArrays(GL_LINES, 0, numGridLines);
    glBindVertexArray(0);
}

void TileMapEditor::render() {
    if (!editorMode || !map) return;

    // Draw the tilemap grid
    draw_grid();

    // Draw all tiles in the map
    for (int y = 0; y < map->get_height(); y++) {
        for (int x = 0; x < map->get_width(); x++) {
            int tileIndex = map->get_tile(x, y);
            if (tileIndex >= 0) {
                glm::vec2 position(x * gridSize.x, y * gridSize.y);
                globals.r->drawTile(tileIndex, position, gridSize);
            }
        }
    }

    // Draw the current tile preview
    // Convert cursor position to screen coordinates and draw preview
    double mouseX, mouseY;
    glfwGetCursorPos(glfwGetCurrentContext(), &mouseX, &mouseY);

    // Snap to grid
    float snapX = floor(mouseX / gridSize.x) * gridSize.x;
    float snapY = floor(mouseY / gridSize.y) * gridSize.y;

    // Draw preview tile at cursor
    globals.r->drawTile(currentTileIndex, glm::vec2(snapX, snapY), gridSize);
}