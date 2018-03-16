;;; odin.el --- specialized comint.el for running the odin.

;; Author: Geoffrey M. Clemm <geoff@cs.colorado.edu>

(require 'comint)

(defvar odin-prompt-pattern "^-> "
  "Regexp to match prompts in the odin shell.")

(defvar odin-default-target "%install"
  "The default target for M-x compile")

(defvar odin-command-regexp "[^;]+"
  "*Regexp to match odin commands.")

(defvar odin-cd-regexp "dir[ \t]*=[ \t]*")


(server-start)

(setq process-environment (cons "EDITOR=emacsclient" (cons "ODINHISTORY=no" (cons "ODINVERIFYLEVEL=0" process-environment))))

(setq after-save-hook (cons 'odin-touch-test
			    (and (boundp 'after-save-hook) after-save-hook)))


(defun odin-mode ()
  (interactive)
  (comint-mode)
  (setq major-mode 'odin-mode)
  (setq mode-name "Odin")
  (setq comint-prompt-regexp odin-prompt-pattern)
  (make-local-variable 'paragraph-start)
  (setq paragraph-start comint-prompt-regexp)
  (add-hook 'comint-input-filter-functions 'odin-directory-tracker nil t)
  (setq comint-input-autoexpand nil)
  (process-kill-without-query (get-buffer-process (current-buffer))))

(defun odin ()
  "Invoke Odin."
  (interactive)
  (setq compile-command (concat "odin "
				(substring default-directory 0 -1)
				odin-default-target))
  (if (not (comint-check-proc "*odin*"))
      (progn
	(set-buffer
	 (make-comint "odin" "odin" nil
		      (concat "!:test;dir="
			      (expand-file-name default-directory) ";!")))
	(odin-mode)))
  (switch-to-buffer "*odin*"))

(defun odin-touch-test ()
  (if (not (comint-check-proc "*.odin.*"))
      (save-excursion
	(set-buffer (make-comint ".odin." "odin" nil))
	(odin-mode)))
  (process-send-string (get-buffer-process "*.odin.*")
		       (concat "'" (buffer-file-name) "'!:test" "\n"))
  nil)

(defun odin-directory-tracker (str)
  (condition-case chdir-failure
      (let ((start (progn (string-match "^[ ;\\s ]*" str) ; skip whitespace
			  (match-end 0)))
	    end cmd)
	(while (string-match odin-command-regexp str start)
	  (setq end (match-end 0)
		cmd (substring str start end))
	  (if (eq (string-match odin-cd-regexp cmd) 0)
	      (let* ((beg (match-end 0))
		     (arg1 (substring cmd beg)))
		(if (not (string-equal arg1 ""))
		    (let ((dir (expand-file-name
				(substitute-in-file-name arg1))))
		      (cd dir)
		      (message dir)))))
	  (setq start (progn (string-match "[ ;\\s ]*" str end)
			     (match-end 0)))))
    (error (message "Couldn't cd"))))

(require 'cc-mode)
(c-add-style "odin"
	     '((c-basic-offset . 3)
	       (c-offsets-alist . ((defun-close           . +)
				   (block-close           . +)
				   (statement-cont . 1)
				   (label . 0)
				   (case-label . +)))))

(provide 'odin)
