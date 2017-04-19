.name "long_runner"
.comment "Champion de ouf"

ld %42, r2
add r2, r3, r4
sti r4, %1, %:live2
live: live %42
live2: live %1
add r5, r6, r7
zjmp %256
