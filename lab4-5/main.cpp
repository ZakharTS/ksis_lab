#include <iostream>

// 6xy - 4y, x + y > 9
// (2xy + 3 + x) / (x^2 + 3y^2 + 1), x + y < -1
// 3x^2 - 2y + 6, -1 <= x + y <= 9

int calculate(const int x, const int y) {
	int result = 0;
	int tmp = 0, tmp1 = 0;
	const int minusOne = -1, one = 1, two = 2, three = 3, four = 4, six = 6, nine = 9;
	__asm {
		; x + y
		fild x; загружаем x в вершину стека
		fiadd y; прибавляем y
		
		ficom nine; если больше 9, то считаем по первой формуле
		fstsw ax
		sahf
		jz calc3
		jnc calc1
		
		ficom minusOne; если меньше -1, то считаем по второй формуле
		fstsw ax
		sahf
		jz calc3
		jc calc2
		
		jmp calc3; иначе считаем по третьей формуле

	calc1 : ; первая формула
		fild y		; st(0) = y
		fimul four	; st(0) = 4y
		fistp tmp	; tmp = 4y

		fild x		; st(0) = x
		fimul y		; st(0) = xy
		fimul six	; st(0) = 6xy
		fisub tmp	; st(0) = 6xy - 4y
		
		jmp finish	; переход к finish

	calc2:; вторая формула
		fild y		; st(0) = y
		fimul y		; st(0) = y ^ 2
		fimul three	; st(0) = 3y^2
		fistp tmp	; tmp = 3y ^ 2

		fild x		; st(0) = x
		fimul x		; st(0) = x^2
		fiadd tmp	; st(0) = x^2 + 3y^2
		fiadd one	; st(0) = x^2 + 3y^2 + 1
		fistp tmp	; tmp =  x^2 + 3y^2 + 1

		fild x		; st(0) = x
		fimul y		; st(0) = xy
		fimul two	; st(0) = 2xy
		fiadd three	; st(0) = 2xy + 3
		fiadd x		; st(0) = 2xy + 3 + x
		fidiv tmp	; st(0) = (2xy + 3 + x) / (x ^ 2 + 3y ^ 2 + 1)
				
		jmp finish	; переход к finish

	calc3 : ; третья формула
		fild y		; st(0) = y
		fimul two	; st(0) = 2y
		fistp tmp	; tmp = 2y

		fild x		; st(0) = x
		fimul x		; st(0) = x^2
		fimul three	; st(0) = 3x^2
		fisub tmp	; st(0) = 3x^2 - 2y
		fiadd six	; st(0) = 3x^2 - 2y + 6

		finish:
		fistp result; результат вычислений в result

	}
	return result;
}

float calculate(const float x, const float y) {
	float result = 0;
	float tmp = 0, tmp1 = 0;
	const float minusOne = -1.0, one = 1.0, two = 2.0, three = 3.0, four = 4.0, six = 6.0, nine = 9.0;
	__asm {
		; x + y
		fld x; загружаем x в вершину стека
		fadd y; прибавляем y

		fcom nine; если больше 9, то считаем по первой формуле
		fstsw ax
		sahf
		jz calc3
		jnc calc1

		fcom minusOne; если меньше - 1, то считаем по второй формуле
		fstsw ax
		sahf 
		jz calc3
		jc calc2

		jmp calc3; иначе считаем по третьей формуле

		calc1 : ; первая формула
		fld y; st(0) = y
		fmul four; st(0) = 4y
		fstp tmp; tmp = 4y

		fld x; st(0) = x
		fmul y; st(0) = xy
		fmul six; st(0) = 6xy
		fsub tmp; st(0) = 6xy - 4y

		jmp fnish; переход к fnish

		calc2 : ; вторая формула
		fld y; st(0) = y
		fmul y; st(0) = y ^ 2
		fmul three; st(0) = 3y ^ 2
		fstp tmp; tmp = 3y ^ 2

		fld x; st(0) = x
		fmul x; st(0) = x ^ 2
		fadd tmp; st(0) = x ^ 2 + 3y ^ 2
		fadd one; st(0) = x ^ 2 + 3y ^ 2 + 1
		fstp tmp; tmp = x ^ 2 + 3y ^ 2 + 1

		fld x; st(0) = x
		fmul y; st(0) = xy
		fmul two; st(0) = 2xy
		fadd three; st(0) = 2xy + 3
		fadd x; st(0) = 2xy + 3 + x
		fdiv tmp; st(0) = (2xy + 3 + x) / (x ^ 2 + 3y ^ 2 + 1)

		jmp fnish; переход к fnish

		calc3 : ; третья формула
		fld y; st(0) = y
		fmul two; st(0) = 2y
		fstp tmp; tmp = 2y

		fld x; st(0) = x
		fmul x; st(0) = x ^ 2
		fmul three; st(0) = 3x ^ 2
		fsub tmp; st(0) = 3x ^ 2 - 2y
		fadd six; st(0) = 3x ^ 2 - 2y + 6

		fnish:
		fstp result; результат вычислений в result

	}
	return result;
}

int main() {
	std::cout << "Choose mode (INT or FLOAT): ";
	std::string mode;
	std::cin >> mode;
	if (mode == "INT") {
		int x, y;
		std::cin >> x >> y;
		std::cout << calculate(x, y) << std::endl;
	}
	else if (mode == "FLOAT") {
		float x, y;
		std::cin >> x >> y;
		std::cout << calculate(x, y) << std::endl;
	}
	else {
		std::cout << "Unknown mode" << std::endl;
	}
	return 0;
}