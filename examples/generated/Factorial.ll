; ModuleID = 'OplLLVM'
source_filename = "OplLLVM"

%Main = type { ptr }

@vtableClass = global [0 x ptr] zeroinitializer
@vtableAnyValue = global [0 x ptr] zeroinitializer
@vtableMain = global [1 x ptr] [ptr @Factorial_Integer_Main_]

declare i1 @Boolean_Boolean_(i1)

declare i64 @toInteger_Boolean_(i1)

declare i1 @Or_Boolean_Boolean_(i1, i1)

declare i1 @And_Boolean_Boolean_(i1, i1)

declare i1 @Xor_Boolean_Boolean_(i1, i1)

declare i1 @Not_Boolean_(i1)

declare i64 @toInteger_Real_(double)

declare i64 @Print_Integer_(i64)

declare i64 @Integer_Integer_(i64)

declare i64 @Integer_()

declare i64 @Plus_Integer_Integer_(i64, i64)

declare i64 @Minus_Integer_Integer_(i64, i64)

declare i64 @Mult_Integer_Integer_(i64, i64)

declare i64 @Div_Integer_Integer_(i64, i64)

declare i1 @Less_Integer_Integer_(i64, i64)

declare i1 @LessEqual_Integer_Integer_(i64, i64)

declare i1 @Equal_Integer_Integer_(i64, i64)

define i64 @Factorial_Integer_Main_(i64 %a, ptr %this) {
entry:
  %_tmpMinus_Integer_Integer_ = alloca i64, align 8
  %_tmpMult_Integer_Integer_ = alloca i64, align 8
  %_tmpLessEqual_Integer_Integer_ = alloca i64, align 8
  %this2 = alloca ptr, align 8
  %a1 = alloca i64, align 8
  store i64 %a, ptr %a1, align 4
  store ptr %this, ptr %this2, align 8
  %a3 = load i64, ptr %a1, align 4
  store i64 %a3, ptr %_tmpLessEqual_Integer_Integer_, align 4
  %0 = load i64, ptr %_tmpLessEqual_Integer_Integer_, align 4
  %calltmp = call i1 @LessEqual_Integer_Integer_(i64 1, i64 %0)
  %ifcond = icmp ne i1 %calltmp, false
  br i1 %ifcond, label %then, label %else

then:                                             ; preds = %entry
  ret i64 1

else:                                             ; preds = %entry
  br label %ifcont

ifcont:                                           ; preds = %else
  %a4 = load i64, ptr %a1, align 4
  store i64 %a4, ptr %_tmpMult_Integer_Integer_, align 4
  %1 = load ptr, ptr %this2, align 8
  %this.vtableMain = getelementptr inbounds %Main, ptr %1, i32 0, i32 0
  %2 = load ptr, ptr %this.vtableMain, align 8
  %3 = getelementptr inbounds [1 x ptr], ptr %2, i32 0, i32 0
  %Factorial_Integer_Main_ = load ptr, ptr %3, align 8
  %a5 = load i64, ptr %a1, align 4
  store i64 %a5, ptr %_tmpMinus_Integer_Integer_, align 4
  %4 = load i64, ptr %_tmpMinus_Integer_Integer_, align 4
  %calltmp6 = call i64 @Minus_Integer_Integer_(i64 1, i64 %4)
  %5 = load %Main, ptr %this2, align 8
  %calltmp7 = call i64 %Factorial_Integer_Main_(i64 %calltmp6, %Main %5)
  %6 = load i64, ptr %_tmpMult_Integer_Integer_, align 4
  %calltmp8 = call i64 @Mult_Integer_Integer_(i64 %calltmp7, i64 %6)
  ret i64 %calltmp8
}

define %Main @Main_() {
entry:
  %_tmpPrint_Integer_ = alloca i64, align 8
  %a = alloca i64, align 8
  %this = alloca %Main, align 8
  %this.vtableMain = getelementptr inbounds %Main, ptr %this, i32 0, i32 0
  store ptr @vtableMain, ptr %this.vtableMain, align 8
  %this.vtableMain1 = getelementptr inbounds %Main, ptr %this, i32 0, i32 0
  %0 = load ptr, ptr %this.vtableMain1, align 8
  %1 = getelementptr inbounds [1 x ptr], ptr %0, i32 0, i32 0
  %Factorial_Integer_Main_ = load ptr, ptr %1, align 8
  %calltmp = call i64 %Factorial_Integer_Main_(i64 7, ptr %this)
  store i64 %calltmp, ptr %a, align 4
  %a2 = load i64, ptr %a, align 4
  store i64 %a2, ptr %_tmpPrint_Integer_, align 4
  %2 = load i64, ptr %_tmpPrint_Integer_, align 4
  %calltmp3 = call i64 @Print_Integer_(i64 %2)
  %3 = load %Main, ptr %this, align 8
  ret %Main %3
}

define i32 @main() {
entry:
  %0 = call %Main @Main_()
  ret i32 0
}
