Habeen Jun (hj316)
YunHyuk Chang (yc1128)

<test plan>
(a) what properties your library must have for you to consider it correct?

(b) How you intend to check that your code has these properties?

(c) Specific method(s) you will use to check each property

<descriptions of test programs>
<performance test>
    There are 5 functions that test out each stress test.

    double test_performance1()
    double test_performance2()
    double test_performance3()
    double test_performance4()
    double test_performance5()

    There's a comment inside each function describing which test it's performing. 

    Only for test_performance3(), there 
    are two helper functions: 
        allocate_1byte_chunck_in_arr(void **arr, int index)
        deallocate_chunck_in_arr(void **arr, int index)
    These functions are called randomly until we call 
    allocate_1byte_chunck_in_arr 120 times.

    And there is a main performance test function 
    (void execute_performance_tests())
    calling each test function 50 times and prints out average time taken for each function.

<correctness test>
