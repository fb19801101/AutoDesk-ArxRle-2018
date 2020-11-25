; MODULE_ID ACAD2007_LSP_
;;;    ACAD2018.LSP Version 1.0 for AutoCAD 2018
;;;
;;;  Copyright 2017 Autodesk, Inc.  All rights reserved.
;;;
;;;  Use of this software is subject to the terms of the Autodesk license 
;;;  agreement provided at the time of installation or download, or which 
;;;  otherwise accompanies this software in either electronic or hard copy form.
;;;
;;;
;;;
;;;    Note:
;;;            This file is normally loaded only once per AutoCAD session.
;;;            If you wish to have LISP code loaded into every document,
;;;            you should add your code to acaddoc.lsp.
;;;
;;;    Globalization Note:   
;;;            We do not support autoloading applications by the native 
;;;            language command call (e.g. with the leading underscore
;;;            mechanism.)

(if (not (=  (substr (ver) 1 11) "Visual LISP")) (load "acad2018doc.lsp"))
(arxload "ArxRle.arx")

;; Silent load.
(princ)


;;;-----BEGIN-SIGNATURE-----
;;; cQcAADCCB20GCSqGSIb3DQEHAqCCB14wggdaAgEBMQ8wDQYJKoZIhvcNAQELBQAw
;;; CwYJKoZIhvcNAQcBoIIFBzCCBQMwggProAMCAQICEHZytCYU0up+ZBBTpYM4hJYw
;;; DQYJKoZIhvcNAQELBQAwgYQxCzAJBgNVBAYTAlVTMR0wGwYDVQQKExRTeW1hbnRl
;;; YyBDb3Jwb3JhdGlvbjEfMB0GA1UECxMWU3ltYW50ZWMgVHJ1c3QgTmV0d29yazE1
;;; MDMGA1UEAxMsU3ltYW50ZWMgQ2xhc3MgMyBTSEEyNTYgQ29kZSBTaWduaW5nIENB
;;; IC0gRzIwHhcNMTYwODA4MDAwMDAwWhcNMTcwOTAyMjM1OTU5WjCBiDELMAkGA1UE
;;; BhMCVVMxEzARBgNVBAgMCkNhbGlmb3JuaWExEzARBgNVBAcMClNhbiBSYWZhZWwx
;;; FjAUBgNVBAoMDUF1dG9kZXNrLCBJbmMxHzAdBgNVBAsMFkRlc2lnbiBTb2x1dGlv
;;; bnMgR3JvdXAxFjAUBgNVBAMMDUF1dG9kZXNrLCBJbmMwggEiMA0GCSqGSIb3DQEB
;;; AQUAA4IBDwAwggEKAoIBAQDqmfToz8wEanfXT+H6tql3aUyaJRWCfFsYPFnGVXIl
;;; 95fnZY3sOEfQvFkf9LVte5SwDWkjkReCGJlk4HaRYOTxkd7PkeAOOtYaUSBvULYR
;;; lKvAbe2n+VWwo4yrWATav8d7pKlbMP9f6pYxlaZQzsq/e+pLZwptP8C9Dfrm5OVg
;;; CIL/iPRNIuvhl9YUZvnkZYmCnihdP4AS8g4d7rfjdxzT653433nO6tgs3fNgnkQQ
;;; k6EdROwqesgQXRlH29yRND5xNfup9KiZ7L7Nm7AiM6laNwNIjBwbG4qMWuQ2Ml7h
;;; HzQpLaLFJRV33oHedeGSZ7OmA6+D5WoQtPpSt4YCcub5AgMBAAGjggFpMIIBZTAJ
;;; BgNVHRMEAjAAMA4GA1UdDwEB/wQEAwIHgDATBgNVHSUEDDAKBggrBgEFBQcDAzBh
;;; BgNVHSAEWjBYMFYGBmeBDAEEATBMMCMGCCsGAQUFBwIBFhdodHRwczovL2Quc3lt
;;; Y2IuY29tL2NwczAlBggrBgEFBQcCAjAZDBdodHRwczovL2Quc3ltY2IuY29tL3Jw
;;; YTAfBgNVHSMEGDAWgBTUwAYiSes5S92T4lyhuEd2CXIDWDArBgNVHR8EJDAiMCCg
;;; HqAchhpodHRwOi8vcmIuc3ltY2IuY29tL3JiLmNybDBXBggrBgEFBQcBAQRLMEkw
;;; HwYIKwYBBQUHMAGGE2h0dHA6Ly9yYi5zeW1jZC5jb20wJgYIKwYBBQUHMAKGGmh0
;;; dHA6Ly9yYi5zeW1jYi5jb20vcmIuY3J0MBEGCWCGSAGG+EIBAQQEAwIEEDAWBgor
;;; BgEEAYI3AgEbBAgwBgEBAAEB/zANBgkqhkiG9w0BAQsFAAOCAQEAwDtvZOfelquc
;;; pqTk6GC5mkXO2Xhr2Meo+ZTVpsAgvQAi0zfpqlxdZrH+SrR0R06cixVQx/8wgty6
;;; 0cx0h7n5YZChZYSULBLbWd64ZisZRLSfOSHfaQPMJlzfkObSiErUXli7GdngNeRv
;;; QRBZj76uQwBY9IfizReoavOwtm1aoptvSn/cAzKdzXXe4Y9O0BFYewqgihKACWL1
;;; 0QQQHazE6owk7WAsA5AGgIOS3RJucO+owkJEdl8yjk4A5amvbkCMkAQHNnIul/Tg
;;; XRicNGTNCQ5RJEaa97jg7WSDp1EEHISPpPnMBACu/rxYX7CwYuw8rdZm73yDa/NN
;;; 3BY2t4uSTjGCAiowggImAgEBMIGZMIGEMQswCQYDVQQGEwJVUzEdMBsGA1UEChMU
;;; U3ltYW50ZWMgQ29ycG9yYXRpb24xHzAdBgNVBAsTFlN5bWFudGVjIFRydXN0IE5l
;;; dHdvcmsxNTAzBgNVBAMTLFN5bWFudGVjIENsYXNzIDMgU0hBMjU2IENvZGUgU2ln
;;; bmluZyBDQSAtIEcyAhB2crQmFNLqfmQQU6WDOISWMA0GCSqGSIb3DQEBCwUAMA0G
;;; CSqGSIb3DQEBAQUABIIBAJA5/FNKk/9wOjSzhgoqW2V30F00ZPG9UfnlYu5mpkMH
;;; 6GtU/8UR8tCmD9dAjgYssER/HfMXV37Df3faunWQDbXadsF5vrUeIUx8q1KfVw1t
;;; ZF7QXvNMhSukXUGgxoQRi8mbTaBPw82MBOfKotpsYG9CxoTdOQEnf/TVHSsc0609
;;; N2I8QSHgPAsJAXQIn8e0HFNSQYKj02JVif+KwWEI1Pqbot6DH03UhfFN64QzJsL3
;;; VA8j4EWMk9QEmI66GYroWdTyC+iQ3ZvOWhDNYlNJKBTZuC2oqp9o1HCQq+zVtCpX
;;; RCtB0kZynzelZm6jUQNzisK4P/rLST7I+J8pA0Y6FaKhYzBhBgNVHQ4xWgRYNAAw
;;; ADsAMgAvADMALwAyADAAMQA3AC8ANAAvADUAMAAvADUAMwAvAFQAaQBtAGUAIABm
;;; AHIAbwBtACAAdABoAGkAcwAgAGMAbwBtAHAAdQB0AGUAcgAAAA==
;;; -----END-SIGNATURE-----