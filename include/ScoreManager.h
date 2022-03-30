#pragma once

void reset_score();

void increment_score_line_clear(int num_line_clears);

void increment_score_on_commit(int num_soft_drop_cells, int num_hard_drop_cells);

void game_over();