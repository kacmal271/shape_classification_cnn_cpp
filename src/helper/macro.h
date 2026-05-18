#ifndef FUNCTION_MACRO_H
#define FUNCTION_MACRO_H

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

///
/// preprocessor macros

#define dump(A) (std::cout << "\n" << (#A) << "=" << (A))

#define whereAmI() (std::cout << "Currently in function " << __func__ << "() on line " << __LINE__)

#endif // FUNCTION_MACRO_H
