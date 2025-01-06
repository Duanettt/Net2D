#include "TileMapEditor.h"
#include "../Graphics/Renderer.h"

TileMapEditor::TileMapEditor(Tilemap* mp, Tileset* ts, glm::vec2 cs) : map(mp), tileset(ts), currentTile(0), isEditing(false), gridSize(cs)
{

}

void TileMapEditor::handle_input(GLFWwindow* window, double mouseX, double mouseY)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		map->set_tile(mouseX, mouseY, 0);
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		map->clear_tile(mouseX, mouseY);
	}


}

void TileMapEditor::set_current_tile(int tileIndex)
{
	currentTile = tileIndex;
}

void TileMapEditor::setup_grid(Renderer& renderer)
{
    // Draw vertical lines
    for (int x = 0; x <= map->get_width(); x++) {
        float xPos = x * gridSize.x;
        globals.r->setup_line_renderer(
            glm::vec2(xPos, 0),
            glm::vec2(xPos, map->get_height() * gridSize.y),
            glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)
        );
    }

    // Draw horizontal lines
    for (int y = 0; y <= map->get_height(); y++) {
        float yPos = y * gridSize.y;
        globals.r->setup_line_renderer(
            glm::vec2(0, yPos),
            glm::vec2(map->get_width() * gridSize.x, yPos),
            glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)
        );
    }
}

void TileMapEditor::draw_grid(Renderer& renderer)
{
    globals.r->draw_line();
}

void TileMapEditor::render(Renderer& renderer)
{
    // Draw the tilemap
    for (int y = 0; y < map->get_height(); y++) {
        for (int x = 0; x < map->get_width(); x++) {
            int tileIndex = map->get_tile(x, y);
            if (tileIndex >= 0) {
                glm::vec2 position(x * gridSize.x, y * gridSize.y);
                globals.r->drawTile(tileIndex, position, gridSize);
            }
        }
    }


    draw_grid(renderer);
}



