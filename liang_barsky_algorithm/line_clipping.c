#include <stdio.h>
#include <stdlib.h>

#ifndef LINE_CLIPPING_DATA
struct _point {
	float x;
	float y;
};
typedef struct _point POINT;

struct _line {
	POINT start;
	POINT end;
};
typedef struct _line LINE;

struct _window {
	POINT point;
	int width;
	int height;
};
typedef struct _window WINDOW;
#endif

#ifndef LINE_CLIPPING_DATA_OPERATIONS

#define window_x_left(w) w.point.x
#define window_x_right(w) (w.point.x+w.width)
#define window_y_bottom(w) w.point.y
#define window_y_top(w) (w.point.y+w.height)

#define line_x_i(l) l.start.x
#define line_x_f(l) l.end.x
#define line_y_i(l) l.start.y
#define line_y_f(l) l.end.y

#define line_x_dif(l) (l.end.x-l.start.x)
#define line_y_dif(l) (l.end.y-l.start.y)

POINT* left_analysis(LINE, WINDOW);
POINT* right_analysis(LINE, WINDOW);
POINT* top_analysis(LINE, WINDOW);
POINT* bottom_analysis(LINE, WINDOW);
void liang_barsky(FILE*, FILE*, char**);
int is_inside_window(POINT*, WINDOW);
#endif



POINT* left_analysis(LINE l, WINDOW w) {
	float u, y;
	POINT *pclipping;
	if (line_x_dif(l) == 0) {
		return NULL;
	}
	u = (float)((window_x_left(w) - line_x_i(l)) / line_x_dif(l));
	if (u < 0 || u > 1) {
		return NULL;
	}
	y = line_y_i(l) + u*(line_y_dif(l));
	pclipping = (POINT *) malloc(sizeof(POINT));
	pclipping->x = window_x_left(w);
	pclipping->y = y;
	if (!is_inside_window(pclipping,w)) {
		return NULL;
	}
	return pclipping;
}

POINT* right_analysis(LINE l, WINDOW w) {
	float u, y;
	POINT *pclipping;
	if (line_x_dif(l) == 0) {
		return NULL;
	}
	u = (float)((window_x_right(w) - line_x_i(l)) / line_x_dif(l));
	if (u < 0 || u > 1) {
		return NULL;
	}
	y = line_y_i(l) + u*(line_y_dif(l));
	pclipping = (POINT *) malloc(sizeof(POINT));
	pclipping->x = window_x_right(w);
	pclipping->y = y;
	if (!is_inside_window(pclipping,w)) {
		return NULL;
	}
	return pclipping;
}

POINT* bottom_analysis(LINE l, WINDOW w) {
	float u, x;
	POINT *pclipping;
	if (line_y_dif(l) == 0) {
		return NULL;
	}
	u = (float)((window_y_bottom(w) - line_y_i(l)) / line_y_dif(l));
	if (u < 0 || u > 1) {
		return NULL;
	}
	x = line_x_i(l) + u*(line_x_dif(l));
	pclipping = (POINT *) malloc(sizeof(POINT));
	pclipping->x = x;
	pclipping->y = window_y_bottom(w);
	if (!is_inside_window(pclipping,w)) {
		return NULL;
	}
	return pclipping;
}

POINT* top_analysis(LINE l, WINDOW w) {
	float u, x;
	POINT *pclipping;
	if (line_y_dif(l) == 0) {
		return NULL;
	}
	u = (float)((window_y_top(w) - line_y_i(l)) / line_y_dif(l));
	if (u < 0 || u > 1) {
		return NULL;
	}
	x = line_x_i(l) + u*(line_x_dif(l));
	pclipping = (POINT *) malloc(sizeof(POINT));
	pclipping->x = x;
	pclipping->y = window_y_top(w);
	if (!is_inside_window(pclipping,w)) {
		return NULL;
	}
	return pclipping;
}

void liang_barsky(FILE *input, FILE *output, char **argv) {
	int index = 0, i;
	LINE *lines = (LINE *) malloc(sizeof(LINE));
	WINDOW w;
	w.point.x = atof(argv[3]);
	w.point.y = atof(argv[4]);
	w.width = atoi(argv[5]);
	w.height = atoi(argv[6]);
	while(!feof(input)) {
		lines = (LINE*) realloc(lines, (index + 1)*sizeof(LINE));
		fscanf(input, "%f %f %f %f", &lines[index].start.x, &lines[index].start.y,
									 &lines[index].end.x, &lines[index].end.y);
		index++;
	}
	for(i = 0; i < index; i++) {
		POINT *p;
		if((p=left_analysis(lines[i],w)) != NULL)
			fprintf(output, "Left analysis: (%.3f, %.3f).\n", p->x, p->y);
		else
			fprintf(output, "Left analysis: has no clipping point.\n");
		if((p=right_analysis(lines[i],w)) != NULL)
			fprintf(output, "Right analysis: (%.3f, %.3f).\n", p->x, p->y);
		else
			fprintf(output, "Right analysis: has no clipping point.\n");
		if((p=top_analysis(lines[i],w)) != NULL)
			fprintf(output, "Top analysis: (%.3f, %.3f).\n", p->x, p->y);
		else
			fprintf(output, "Top analysis: has no clipping point.\n");
		if((p=bottom_analysis(lines[i],w)) != NULL)
			fprintf(output, "Bottom analysis: (%.3f, %.3f).\n", p->x, p->y);
		else
			fprintf(output, "Bottom analysis: has no clipping point.\n");
		fprintf(output, "\n");
	}
	free(lines);
}

int is_inside_window(POINT* p, WINDOW w) {
	if (p->x < window_x_left(w) || p->x > window_x_right(w)) {
		return 0;
	} else if (p->y < window_y_bottom(w) || p->y > window_y_top(w)) {
		return 0;
	} else {
		return 1;
	}
}

int main(int argc, char **argv) {
	FILE *input, *output;
	if (argc < 7) {
		printf("Usage: ./liang-barsky input output x y width height\n");
		exit(EXIT_FAILURE);
	}
	if (!(input = fopen(argv[1], "r"))) {
		perror("File error");
		exit(EXIT_FAILURE);
	}
	if(!(output = fopen(argv[2], "w"))) {
		perror("File error");
		exit(EXIT_FAILURE);
	}
	liang_barsky(input, output, argv);
	fclose(input);
	fclose(output);
	return 0;
}