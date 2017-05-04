// Copyright 2013 Lee Calloway
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#import <UIKit/UIKit.h>

#import "IBStringValidator.h"


/**
 Allows setting an IBStringValidator onto a UITextField. Once set, the string validator
 state is automatically updated whenever the UITextField text changes. In turn, the
 validBlock and invalidBlock on the string validator will be called when the validity
 of the UITextField text changes.
 */
@interface UITextField (IBTextValidation)

/**
 Accessor for a string validator that has been associated with the UITextField.
 */
- (IBStringValidator*)ibStringValidator;

/**
 Associates a string validator with the UITextField.
 @param stringValidator The string validator to associate with the UITextField.
 */
- (void)ibSetStringValidator:(IBStringValidator*)stringValidator;

@end
