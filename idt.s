.extern idtp
.global idtldr

idtldr:
	lidt idtp
	ret
