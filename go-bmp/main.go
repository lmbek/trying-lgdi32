package main

import (
	"fmt"
	"unsafe"
)

// #cgo LDFLAGS: -lgdi32 -luser32 -lgdiplus
// #include "program.c"
import "C"

// NOTE: it is important to run "go clean -cache" often with the terminal/cmd as compiling C code is a pain with Go for me at least :-)

func main() {
	// Define parameters

	hInstance := C.HINSTANCE(unsafe.Pointer(uintptr(0))) // Replace with the actual values
	hPrevInstance := C.HINSTANCE(unsafe.Pointer(uintptr(0)))
	lpCmdLine := C.CString("your command line arguments") // Replace with actual command line arguments
	nCmdShow := C.int(1)                                  // Replace with the actual value

	// Call the C function with the parameters
	result := C.start(hInstance, hPrevInstance, lpCmdLine, nCmdShow)

	// Clean up
	C.free(unsafe.Pointer(lpCmdLine))

	fmt.Printf("C code returned: %d\n", int(result))
}
