; ModuleID = 'OplLLVM'
source_filename = "OplLLVM"

%Main = type { ptr }

@vtableClass = global [0 x ptr] zeroinitializer
@vtableAnyValue = global [0 x ptr] zeroinitializer
@vtableMain = global [0 x ptr] zeroinitializer

declare i1 @Boolean_Boolean_(i1)

declare i64 @toInteger_Boolean_(i1)

declare i1 @Or_Boolean_Boolean_(i1, i1)

declare i1 @And_Boolean_Boolean_(i1, i1)

declare i1 @Xor_Boolean_Boolean_(i1, i1)

declare i1 @Not_Boolean_(i1)

declare i64 @toInteger_Real_(double)

declare i1 @Greater_Integer_Real_(i64, double)

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

define %Main @Main_() {
entry:
  %__tmpLess_Integer_Integer_6 = alloca i64, align 8
  %__tmpPlus_Integer_Integer_ = alloca i64, align 8
  %__tmpPrint_Integer_ = alloca i64, align 8
  %__tmpLess_Integer_Integer_ = alloca i64, align 8
  %i = alloca i64, align 8
  %this = alloca %Main, align 8
  %this.vtableMain = getelementptr inbounds %Main, ptr %this, i32 0, i32 0
  store ptr @vtableMain, ptr %this.vtableMain, align 8
  store i64 0, ptr %i, align 4
  %i1 = load i64, ptr %i, align 4
  store i64 %i1, ptr %__tmpLess_Integer_Integer_, align 4
  %0 = load i64, ptr %__tmpLess_Integer_Integer_, align 4
  %calltmp = call i1 @Less_Integer_Integer_(i64 10, i64 %0)
  br label %loop

loop:                                             ; preds = %loop, %entry
  %i2 = load i64, ptr %i, align 4
  store i64 %i2, ptr %__tmpPrint_Integer_, align 4
  %1 = load i64, ptr %__tmpPrint_Integer_, align 4
  %calltmp3 = call i64 @Print_Integer_(i64 %1)
  %i4 = load i64, ptr %i, align 4
  store i64 %i4, ptr %__tmpPlus_Integer_Integer_, align 4
  %2 = load i64, ptr %__tmpPlus_Integer_Integer_, align 4
  %calltmp5 = call i64 @Plus_Integer_Integer_(i64 1, i64 %2)
  store i64 %calltmp5, ptr %i, align 4
  %i7 = load i64, ptr %i, align 4
  store i64 %i7, ptr %__tmpLess_Integer_Integer_6, align 4
  %3 = load i64, ptr %__tmpLess_Integer_Integer_6, align 4
  %calltmp8 = call i1 @Less_Integer_Integer_(i64 10, i64 %3)
  %loopcond = icmp ne i1 %calltmp8, false
  br i1 %loopcond, label %loop, label %afterloop

afterloop:                                        ; preds = %loop
  %4 = load %Main, ptr %this, align 8
  ret %Main %4
}

define i32 @main() {
entry:
  %0 = call %Main @Main_()
  ret i32 0
}
