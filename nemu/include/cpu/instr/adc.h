#ifndef __INSTR_ADC_H__
#define __INSTR_ADC_H__

make_instr_func(adc, r, rm, b);
make_instr_func(adc, r, rm, v);
make_instr_func(adc, rm, r, b);
make_instr_func(adc, rm, r, v);
make_instr_func(adc, i, a, b);
make_instr_func(adc, i, a, v);

#endif
