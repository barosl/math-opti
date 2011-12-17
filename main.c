#include <stdio.h>
#include <math.h>

#define MAX_COEFFS 11

static double func_coeffs[MAX_COEFFS];
static int func_order;

static double gd_rat;
static void init_golden_ratio() {
	gd_rat = (sqrt(5)-1)/2;
}

static int input_func() {
	int i;

	printf("> Order: ");
	if (scanf("%d", &func_order) != 1) return -1;
	if (func_order < 0 || func_order >= MAX_COEFFS) return -1;

	printf("> Coefficients: ");
	for (i=func_order;i>=0;i--) {
		if (scanf("%lf", &func_coeffs[i]) != 1) return -1;
	}

	return 0;
}

static double eval_func(double x) {
	int i;

	double sum = 0;
	double cur_x = 1;
	for (i=0;i<=func_order;i++) {
		sum += func_coeffs[i]*cur_x;
		cur_x *= x;
	}

	return sum;
}

static double golden_sect_srch() {
	int i;

	double xl, xu, es;
	int i_max;

	double x_opt;
	double d, x1, x2;

	printf(">> xl = ");
	scanf("%lf", &xl);
	printf(">> xu = ");
	scanf("%lf", &xu);
	printf(">> es = ");
	scanf("%lf", &es);
	printf(">> i_max = ");
	scanf("%d", &i_max);

	/*
	xl = -4;
	xu = 2;
	es = 0.005;
	i_max = 10000;
	*/

	d = gd_rat*(xu - xl);
	x1 = xl + d;
	x2 = xu - d;

	x_opt = 0;

	for (i=0;i<i_max;i++) {
		if (eval_func(x1) > eval_func(x2)) {
			xl = x2;
			x2 = x1;
			x1 = xl + gd_rat*(xu - xl);

			x_opt = x1;
		} else {
			xu = x1;
			x1 = x2;
			x2 = xu - gd_rat*(xu - xl);

			x_opt = x2;
		}

		if (i != 0 && fabs((1 - gd_rat)/(xu - xl)) < es) break;
	}

	return x_opt;
}

static double quadratic_interpolation() {
	int i;

	double x0, x1, x2, es;
	int i_max;

	double x_opt, old_x_opt;

	printf(">> x0 = ");
	scanf("%lf", &x0);
	printf(">> x1 = ");
	scanf("%lf", &x1);
	printf(">> x2 = ");
	scanf("%lf", &x2);
	printf(">> es = ");
	scanf("%lf", &es);
	printf(">> i_max = ");
	scanf("%d", &i_max);

	/*
	x0 = -4;
	x1 = -3;
	x2 = 2;
	es = 0.005;
	i_max = 10000;
	*/

	old_x_opt = x_opt = 0;

	for (i=0;i<i_max;i++) {
		x_opt = (eval_func(x0)*(x1*x1 - x2*x2) + eval_func(x1)*(x2*x2 - x0*x0) + eval_func(x2)*(x0*x0 - x1*x1))
			/ (2*(eval_func(x0)*(x1 - x2) + eval_func(x1)*(x2 - x0) + eval_func(x2)*(x0 - x1)));

		if (x_opt > x1) {
			x0 = x1;
			x1 = x_opt;
		} else {
			x1 = x_opt;
			x2 = x1;
		}

		if (i != 0 && fabs((x_opt - old_x_opt)/x_opt) < es) break;

		old_x_opt = x_opt;
	}

	return x_opt;
}

int main(void) {
	int choice;
	double x_opt;

	init_golden_ratio();

	if (input_func()) {
		fputs("Invalid input.", stderr);
		return -1;
	}

	/*
	func_order = 2;
	func_coeffs[2] = -1;
	func_coeffs[1] = -2;
	func_coeffs[0] = 10;
	*/

	while (1) {
		printf("1. Golden section search\n2. Quadratic interpolation\n3. Quit\n> ");
		if (scanf("%d", &choice) != 1) break;
		if (choice < 1 || choice > 3) continue;

		if (choice == 3) break;
		x_opt = (choice == 1 ? golden_sect_srch : quadratic_interpolation)();

		printf("* Found optimum = %f (x = %f)\n", eval_func(x_opt), x_opt);
		printf("----\n");
	}

	return 0;
}
